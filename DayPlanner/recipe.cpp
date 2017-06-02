#include "recipe.h"
#include "dao/dao.h"
#include "meal.h"


Recipe::Recipe(QObject *parent)
	: QObject(parent),
	  m_recipe(nullptr),
	  m_items(nullptr),
	  m_dispServings(1)
{
	Q_ASSERT(false);
}

Recipe::Recipe(RecipeDAO *recipe, QObject *parent)
	: QObject(parent),
	  m_recipe(recipe),
	  m_items(nullptr),
	  m_dispServings(1)
{
	m_items = IngredientItemList::loadList(this, globalDAOFacade(), m_recipe->ingredientListId());
	// Forces calculation of mutliplicator and update in ingredient list
	m_dispServings = 0;
	setDisplayServings(1);
	connect(m_items, &IngredientItemList::itemsChanged, this, &Recipe::updateItemSums);
	connect(m_items, &IngredientItemList::sumFatChanged, this, &Recipe::updateFatFromSum);
	connect(m_items, &IngredientItemList::sumProteinChanged, this, &Recipe::updateProteinFromSum);
	connect(m_items, &IngredientItemList::sumCarbsChanged, this, &Recipe::updateCarbsFromSum);
	connect(m_items, &IngredientItemList::sumCaloriesChanged, this, &Recipe::updateCaloriesFromSum);
}

Recipe::~Recipe()
{
	RecipeLoader::instance()->removeRecipe(this);
	delete m_recipe;
}

Recipe *Recipe::loadRecipeById(qint32 id)
{
	RecipeDAO *r = globalDAOFacade()->loadRecipe(id);
	if (!r || r->state() == DAOBase::State::New) {
		delete r;
		return nullptr;
	}

	return new Recipe(r);
}

void Recipe::adjustForServings(qint32 servings)
{
	if (servings <= 0) return;
	if (servings == this->servings()) return;


	qreal f = qreal(servings) / this->servings();
	for (auto i : m_items->ingredients()) {
		i->setQuantity(i->quantity()*f);
	}
	// Update override values
	if (m_recipe->nutritionValuesOverridden()) {
		setFat(fat()*f, true);
		setProtein(protein()*f, true);
		setCarbs(carbs()*f, true);
		setCalories(calories()*f, true);
	}
	setServings(servings);
	setDisplayServings(servings);
}

qint32 Recipe::id() const
{
	return m_recipe->id();
}

IngredientItemList *Recipe::items() const
{
	return m_items;
}

QString Recipe::name() const
{
	return m_recipe->name();
}

qint32 Recipe::servings() const
{
	return m_recipe->referenceServing();
}

qint32 Recipe::defaultServings() const
{
	return m_recipe->defaultServing();
}

qint32 Recipe::displayServings() const
{
	return m_dispServings;
}

qreal Recipe::fat() const
{
	return m_recipe->fat() * multiplicator();
}

qreal Recipe::protein() const
{
	return m_recipe->protein() * multiplicator();
}

qreal Recipe::carbs() const
{
	return m_recipe->carbs() * multiplicator();
}

qreal Recipe::calories() const
{
	return m_recipe->calories() * multiplicator();
}

qreal Recipe::multiplicator() const
{
	return qreal(m_dispServings) / servings();
}

bool Recipe::nutritionValuesOverridden() const
{
	return m_recipe->nutritionValuesOverridden();
}

Meal *Recipe::writeBackMeal() const
{
	return m_writeBack;
}

void Recipe::setName(const QString &n)
{
	if (n != name()) {
		m_recipe->setName(n);
		if (m_recipe->save()) {
			if (m_writeBack) m_writeBack->setName(n);
			emit nameChanged();
		}
	}
}

void Recipe::setServings(qint32 s)
{
	if (s != servings()) {
		m_recipe->setReferenceServing(s);
		if (m_recipe->save()) {
			emit servingsChanged();
			updateItemMultiplicators();
			if (m_writeBack) {
				m_writeBack->setFat(m_recipe->fat()/servings());
				m_writeBack->setProtein(m_recipe->protein()/servings());
				m_writeBack->setCarbs(m_recipe->carbs()/servings());
				m_writeBack->setCalories(m_recipe->calories()/servings());
			}
		}
	}
}

void Recipe::setDefaultServings(qint32 ds)
{
	if (ds != defaultServings()) {
		m_recipe->setDefaultServing(ds);
		if (m_recipe->save()) {
			emit defaultServingsChanged();
		}
	}
}

void Recipe::setDisplayServings(qint32 ds)
{
	if (ds != m_dispServings) {
		if (ds != 0) {
			m_dispServings = ds;
			emit displayServingsChanged();
			updateItemMultiplicators();
		}
	}
}

template <typename T>
bool updateHelper(Recipe *r, RecipeDAO *rd, Meal *wb, void (RecipeDAO::*setValue)(T), T (Recipe::*getValue)() const, void (Meal::*writeBack)(T), T v, bool force) {
	if (force || rd->nutritionValuesOverridden()) {
		T oldValue = (r->*getValue)(); // This value is multiplied
		T newValue = v / r->multiplicator(); // When setting the value, the multpilicator will be applied below
		if (v != oldValue) {
			(rd->*setValue)(newValue);
			if (rd->save()) {
				if (wb) (wb->*writeBack)(newValue / r->servings()); // Must account for servings in writeback!
				return true;
			}
		}
	} else {
		return true;
	}
	return false;
}

void Recipe::setFat(qreal f)
{
	setFat(f, false);
}

void Recipe::setFat(qreal f, bool force)
{
	if (updateHelper(this, m_recipe, m_writeBack, &RecipeDAO::setFat, &Recipe::fat, &Meal::setFat, f, force)) {
		emit fatChanged();
	}
}

void Recipe::overrideFat(qreal f)
{
	setFat(f, true);
}

void Recipe::setProtein(qreal p)
{
	setProtein(p, false);
}

void Recipe::setProtein(qreal p, bool force)
{
	if (updateHelper(this, m_recipe, m_writeBack, &RecipeDAO::setProtein, &Recipe::protein, &Meal::setProtein, p, force)) {
		emit proteinChanged();
	}
}

void Recipe::overrideProtein(qreal p)
{
	setProtein(p, true);
}

void Recipe::setCarbs(qreal c)
{
	setCarbs(c, false);
}

void Recipe::setCarbs(qreal c, bool force)
{
	if (updateHelper(this, m_recipe, m_writeBack, &RecipeDAO::setCarbs, &Recipe::carbs, &Meal::setCarbs, c, force)) {
		emit carbsChanged();
	}
}

void Recipe::overrideCarbs(qreal c)
{
	setCarbs(c, true);
}

void Recipe::setCalories(qreal c)
{
	setCalories(c, false);
}

void Recipe::setCalories(qreal c, bool force)
{
	if (updateHelper(this, m_recipe, m_writeBack, &RecipeDAO::setCalories, &Recipe::calories, &Meal::setCalories, c, force)) {
		emit caloriesChanged();
	}
}

void Recipe::overrideCalories(qreal c)
{
	setCalories(c, true);
}

void Recipe::setNutritionValuesOverridden(bool o)
{
	if (o != nutritionValuesOverridden()) {
		m_recipe->setNutritionValuesOverridden(o);
		emit nutritionValuesOverriddenChanged();
		if (!o) {
			updateFatFromSum();
			updateProteinFromSum();
			updateCarbsFromSum();
			updateCaloriesFromSum();
		}
		m_recipe->save();
	}
}

void Recipe::setWriteBackMeal(Meal *m)
{
	if (m != m_writeBack) {
		m_writeBack = m;
		emit writeBackMealChanged();
		if (m) {
			setDisplayServings(m->quantity());
		}
	}
}

void Recipe::updateFatFromSum()
{
	if (!m_recipe->nutritionValuesOverridden()) {
		setFat(m_items->sumFat(), true);
	}
}

void Recipe::updateProteinFromSum()
{
	if (!m_recipe->nutritionValuesOverridden()) {
		setProtein(m_items->sumProtein(), true);
	}
}

void Recipe::updateCarbsFromSum()
{
	if (!m_recipe->nutritionValuesOverridden()) {
		setCarbs(m_items->sumCarbs(), true);
	}
}

void Recipe::updateCaloriesFromSum()
{
	if (!m_recipe->nutritionValuesOverridden()) {
		setCalories(m_items->sumCalories(), true);
	}
}

void Recipe::updateItemSums()
{
	if (!m_recipe->nutritionValuesOverridden()) {
		setFat(m_items->sumFat(), true);
		setProtein(m_items->sumProtein(), true);
		setCarbs(m_items->sumCarbs(), true);
		setCalories(m_items->sumCalories(), true);
	}
}

void Recipe::updateItemMultiplicators()
{
	m_items->setMultiplicator(multiplicator());
	emit multiplicatorChanged();
	emit fatChanged();
	emit proteinChanged();
	emit carbsChanged();
	emit caloriesChanged();
}

//////////////////////////////////

RecipeLoader *RecipeLoader::instance()
{
	static RecipeLoader inst_;
	return &inst_;
}

Recipe *RecipeLoader::loadRecipeById(qint32 id)
{
	if (m_cache.contains(id)) {
		return m_cache[id];
	}

	Recipe * r = Recipe::loadRecipeById(id);
	if (r) m_cache[id] = r;
	return r;
}

void RecipeLoader::removeRecipe(Recipe *r)
{
	if (r) m_cache.remove(r->id());
}
