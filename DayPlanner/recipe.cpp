#include "recipe.h"
#include "dao/dao.h"
#include <functional>

Recipe::Recipe(QObject *parent)
	: QObject(parent),
	  m_recipe(nullptr),
	  m_items(nullptr)
{
	Q_ASSERT(false);
}

Recipe::Recipe(RecipeDAO *recipe, QObject *parent)
	: QObject(parent),
	  m_recipe(recipe),
	  m_items(nullptr)
{
	m_items = IngredientItemList::loadList(this, globalDAOFacade(), m_recipe->ingredientListId());
	connect(m_items, &IngredientItemList::itemsChanged, this, &Recipe::updateItemSums);
	connect(m_items, &IngredientItemList::sumFatChanged, this, &Recipe::updateFat);
	connect(m_items, &IngredientItemList::sumProteinChanged, this, &Recipe::updateProtein);
	connect(m_items, &IngredientItemList::sumCarbsChanged, this, &Recipe::updateCarbs);
	connect(m_items, &IngredientItemList::sumCaloriesChanged, this, &Recipe::updateCalories);
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

qint32 Recipe::multiplicator() const
{
	return m_items->multiplicator();
}

void Recipe::setName(const QString &n)
{
	if (n != name()) {
		m_recipe->setName(n);
		if (m_recipe->save()) {
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
		}
	}
	// TODO recalculation? more signals?
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

template <typename T>
bool updateHelper(Recipe *r, RecipeDAO *rd, void (RecipeDAO::*setValue)(T), T (Recipe::*getValue)() const, T v) {
	if (!rd->nutritionValuesOverridden()) {
		if (v != (r->*getValue)()) {
			(rd->*setValue)(v / r->multiplicator());
			if (rd->save()) {
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
	if (updateHelper(this, m_recipe, &RecipeDAO::setFat, &Recipe::fat, f)) {
		emit fatChanged();
	}
}

void Recipe::setProtein(qreal p)
{
	if (updateHelper(this, m_recipe, &RecipeDAO::setProtein, &Recipe::protein, p)) {
		emit proteinChanged();
	}
}

void Recipe::setCarbs(qreal c)
{
	if (updateHelper(this, m_recipe, &RecipeDAO::setCarbs, &Recipe::carbs, c)) {
		emit carbsChanged();
	}
}

void Recipe::setCalories(qreal c)
{
	if (updateHelper(this, m_recipe, &RecipeDAO::setCalories, &Recipe::calories, c)) {
		emit caloriesChanged();
	}
}

void Recipe::setMultiplicator(qint32 m)
{
	if (m != multiplicator()) {
		m_items->setMultiplicator(m);
		emit multiplicatorChanged();
	}
}

void Recipe::updateFat()
{
	if (!m_recipe->nutritionValuesOverridden()) {
		setFat(m_items->sumFat());
	}
}

void Recipe::updateProtein()
{
	if (!m_recipe->nutritionValuesOverridden()) {
		setProtein(m_items->sumProtein());
	}
}

void Recipe::updateCarbs()
{
	if (!m_recipe->nutritionValuesOverridden()) {
		setCarbs(m_items->sumCarbs());
	}
}

void Recipe::updateCalories()
{
	if (!m_recipe->nutritionValuesOverridden()) {
		setCalories(m_items->sumCalories());
	}
}

void Recipe::updateItemSums()
{
	if (!m_recipe->nutritionValuesOverridden()) {
		setFat(m_items->sumFat());
		setProtein(m_items->sumProtein());
		setCarbs(m_items->sumCarbs());
		setCalories(m_items->sumCalories());
	}
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
