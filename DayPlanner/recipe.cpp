#include "recipe.h"
#include "dao/dao.h"
#include "recipetemplatelist.h"
#include "meal.h"

class RecipeDAOWrapper
{
public:
	inline RecipeDAOWrapper(RecipeDAO *r) : m_r(r), m_t(nullptr) {}
	inline RecipeDAOWrapper(RecipeTemplateDAO *r) : m_r(nullptr), m_t(r) {}
	inline ~RecipeDAOWrapper() { delete m_t; delete m_r; }

	inline bool isTempate() const { return m_t != nullptr; }
	inline qint32 id() const { return m_t ? m_t->id() : m_r->id(); }
	inline QString name() const { return m_t ? m_t->name() : m_r->name(); }
	inline void setName(const QString &n) { if (m_t) m_t->setName(n); else m_r->setName(n); }
	inline qint32 referenceServing() const { return m_t ? m_t->referenceServing() : m_r->referenceServing(); }
	inline void setReferenceServing(qint32 q) { if (m_t) m_t->setReferenceServing(q); else m_r->setReferenceServing(q); }
	inline qint32 defaultServing() const { return m_t ? m_t->defaultServing() : m_r->defaultServing(); }
	inline void setDefaultServing(qint32 q) { if (m_t) m_t->setDefaultServing(q); else m_r->setDefaultServing(q); }
	inline qreal fat() const { return m_t ? m_t->fat() : m_r->fat(); }
	inline void setFat(qreal f) { if (m_t) m_t->setFat(f); else m_r->setFat(f); }
	inline qreal protein() const { return m_t ? m_t->protein() : m_r->protein(); }
	inline void setProtein(qreal p) { if (m_t) m_t->setProtein(p); else m_r->setProtein(p); }
	inline qreal carbs() const { return m_t ? m_t->carbs() : m_r->carbs(); }
	inline void setCarbs(qreal c) { if (m_t) m_t->setCarbs(c); else m_r->setCarbs(c); }
	inline qreal calories() const { return m_t ? m_t->calories() : m_r->calories(); }
	inline void setCalories(qreal c) { if (m_t) m_t->setCalories(c); else m_r->setCalories(c); }
	inline QString url() const { return m_t ? m_t->url() : m_r->url(); }
	inline void setUrl(const QString &u) { if (m_t) m_t->setUrl(u); else m_r->setUrl(u); }
	inline QString note() const { return m_t ? m_t->note() : m_r->note(); }
	inline void setNote(const QString &n) { if (m_t) m_t->setNote(n); else m_r->setNote(n); }
	inline qint32 ingredientListId() const { return m_t ? m_t->ingredientListId() : m_r->ingredientListId(); }
	inline void setIngredientListId(qint32 id) { if (m_t) m_t->setIngredientListId(id); else m_r->setIngredientListId(id); }
	inline bool nutritionValuesOverridden() const { return m_t ? false : m_r->nutritionValuesOverridden(); }
	inline void setNutritionValuesOverridden(bool o) { if (m_t) ; else m_r->setNutritionValuesOverridden(o); }
	inline qint32 templateId() const { return m_t ? DAOBase::NoItemIndex : m_r->templateId(); }
	inline void setTemplateId(qint32 id) { if (m_t) ; else m_r->setTemplateId(id); }

	inline bool save() { return m_t ? m_t->save() : m_r->save(); }
private:
	RecipeDAO *m_r;
	RecipeTemplateDAO *m_t;
};

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
	  m_recipe(new RecipeDAOWrapper(recipe)),
	  m_items(nullptr),
	  m_dispServings(1)
{
	init();
}

Recipe::Recipe(RecipeTemplateDAO *recipe, QObject *parent)
	: QObject(parent),
	  m_recipe(new RecipeDAOWrapper(recipe)),
	  m_items(nullptr),
	  m_dispServings(1)
{
	init();
}

void Recipe::init()
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

bool Recipe::saveAsTemplate()
{
	if (m_recipe->isTempate()) return false;
	if (isConnectedToTemplate()) return false;

	QScopedPointer<IngredientItemList> ingOrig(IngredientItemList::loadList(nullptr, globalDAOFacade(), m_recipe->ingredientListId()));
	QScopedPointer<RecipeTemplateDAO> tmpl(globalDAOFacade()->createRecipeTemplate());
	QScopedPointer<IngredientItemList> ingCopy(IngredientItemList::loadList(nullptr, globalDAOFacade(), tmpl->ingredientListId()));
	ingOrig->copyInto(ingCopy.data());

	tmpl->setName(m_recipe->name());
	tmpl->setNote(m_recipe->note());
	tmpl->setUrl(m_recipe->url());
	tmpl->setFat(m_recipe->fat());
	tmpl->setProtein(m_recipe->protein());
	tmpl->setCarbs(m_recipe->carbs());
	tmpl->setCalories(m_recipe->calories());
	tmpl->setDefaultServing(m_recipe->defaultServing());
	tmpl->setReferenceServing(m_recipe->referenceServing());

	if (tmpl->save()) {
		m_recipe->setTemplateId(tmpl->id());
		m_recipe->save();
		emit isConnectedToTemplateChanged();
		RecipeTemplateNotifier::instance()->notifyChanges();
		return true;
	}
	return false;
}

qint32 Recipe::id() const
{
	return m_recipe->id();
}

bool Recipe::isTemplate() const
{
	return m_recipe->isTempate();
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

bool Recipe::isConnectedToTemplate() const
{
	if (m_recipe->isTempate()) return false;
	return m_recipe->templateId() != DAOBase::NoItemIndex;
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
bool updateHelper(Recipe *r, RecipeDAOWrapper *rd, Meal *wb, void (RecipeDAOWrapper::*setValue)(T), T (Recipe::*getValue)() const, void (Meal::*writeBack)(T), T v, bool force) {
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
	if (updateHelper(this, m_recipe, m_writeBack, &RecipeDAOWrapper::setFat, &Recipe::fat, &Meal::setFat, f, force)) {
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
	if (updateHelper(this, m_recipe, m_writeBack, &RecipeDAOWrapper::setProtein, &Recipe::protein, &Meal::setProtein, p, force)) {
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
	if (updateHelper(this, m_recipe, m_writeBack, &RecipeDAOWrapper::setCarbs, &Recipe::carbs, &Meal::setCarbs, c, force)) {
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
	if (updateHelper(this, m_recipe, m_writeBack, &RecipeDAOWrapper::setCalories, &Recipe::calories, &Meal::setCalories, c, force)) {
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
	if (m_recipe->isTempate()) return;

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
