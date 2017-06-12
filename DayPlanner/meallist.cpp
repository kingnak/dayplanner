#include "meallist.h"
#include "dao/dao.h"
#include "meal.h"
#include "dao/ingredientdao.h"
#include "ingredientlist.h"
#include "ingredientitemlist.h"
#include "ingredientlistitem.h"
#include "dao/recipedao.h"
#include "recipe.h"

#include <QGuiApplication>
#include <QClipboard>
#include <QtSql>

MealList::MealList(QObject *parent)
    : QObject(parent)
{
}

MealList::~MealList()
{
}

MealList *MealList::loadForDateAndType(QObject *parent, DAOFacade *facade, QDate d, Meal::Type type)
{
    MealList *ret = new MealList(parent);
    ret->m_type = type;
    ret->m_date = d;
    ret->m_facade = facade;

    QList<MealDAO *> meals = facade->loadMeals(d, type);

    for (auto meal : meals) {
        Meal *m = new Meal(meal, ret);
        ret->m_data << m;
		ret->connectSignals(m);
    }

	ret->notifySumsChanged();

    return ret;
}

QQmlListProperty<Meal> MealList::items()
{
	return QQmlListProperty<Meal> (this, nullptr, &MealList::countFunc, &MealList::atFunc);
}

void MealList::createMeal(const QString &name)
{
    MealDAO *m = m_facade->createMeal(m_date, m_type);
    m->setName(name);
    if (m->save()) {
		Meal *md = new Meal(m, this);
		m_data.append(md);
		connectSignals(md);
        emit itemsChanged();
		notifySumsChanged();
    } else {
        delete m;
    }
}

void MealList::createMealForIngredient(qint32 ingredientId)
{
    if (ingredientId < 0) {
        return;
    }

    QScopedPointer<MealDAO> m(m_facade->createMeal(m_date, m_type));
    if (!m) {
        return;
    }

    QScopedPointer<IngredientDAO> r(m_facade->loadIngredient(ingredientId));
    if (!r || r->state() == DAOBase::State::New) {
        return;
    }

	updateMealFromIngredient(m.data(), r.data());

    if (m->save()) {
		Meal *md = new Meal(m.take(), this);
		m_data.append(md);
		connectSignals(md);
        emit itemsChanged();
		notifySumsChanged();
	}
}

void MealList::createMealForRecipe(qint32 recipeId)
{
	if (recipeId < 0) {
		return;
	}

	QScopedPointer<MealDAO> m(m_facade->createMeal(m_date, m_type));
	if (!m) {
		return;
	}

	QScopedPointer<RecipeDAO> r(m_facade->loadRecipe(recipeId));
	if (!r || r->state() == DAOBase::State::New) {
		return;
	}

	updateMealFromRecipe(m.data(), r.data());

	if (m->save()) {
		Meal *md = new Meal(m.take(), this);
		m_data.append(md);
		connectSignals(md);
		emit itemsChanged();
		notifySumsChanged();
	}
}

void MealList::removeMeal(qint32 idx)
{
    if (idx < 0 || idx >= m_data.count()) {
        return;
    }

    Meal *m = m_data.takeAt(idx);
    m->erase();
    m->deleteLater();
	m->disconnect();
	emit itemsChanged();
	notifySumsChanged();
}

bool MealList::createIngredientFromMeal(qint32 idx)
{
	if (idx < 0 || idx >= m_data.count()) {
		return false;
	}

	Meal *m = m_data[idx];
	if (m->isConnected()) {
		return false;
	}

	QScopedPointer<IngredientDAO> r(m_facade->createIngredient(m->name()));
	if (!r || r->state() != DAOBase::State::New) {
		if (tryConnectMealToIngredientByName(m)) {
			m->m_meal->save();
			m->notifyValuesChanged();
		}
		return false;
	}

	r->setDefaultQuantity((m->quantity() == 0) ? 1 : m->quantity());
	r->setReferenceQuantity(100);
	qreal f = qreal(r->defaultQuantity()) / r->referenceQuantity();
	r->setFat(m->calcFat()/f);
	r->setProtein(m->calcProtein()/f);
	r->setCarbs(m->calcCarbs()/f);
	r->setCalories(m->calcCalories()/f);

	if (r->save()) {
		m->setIngredientId(r->id());
		IngredientNotifier::instance()->notifyChanges();
		return true;
	}

	return false;
}

bool MealList::createRecipeFromMeal(qint32 idx)
{
	if (idx < 0 || idx >= m_data.count()) {
		return false;
	}

	Meal *m = m_data[idx];
	if (m->isConnected()) {
		return false;
	}

	QScopedPointer<RecipeDAO> r(m_facade->createRecipe());
	r->setName(m->name());
	r->setDefaultServing(1);
	r->setReferenceServing(1);
	r->setFat(m->calcFat());
	r->setProtein(m->calcProtein());
	r->setCarbs(m->calcCarbs());
	r->setCalories(m->calcCalories());

	if (r->save()) {
		m->setRecipeId(r->id());
		return true;
	}
	return false;
}

bool MealList::createIngredientFromListItem(const IngredientListItemDAO *item)
{
	if (!item) {
		return false;
	}

	QScopedPointer<MealDAO> m(m_facade->createMeal(m_date, m_type));
	if (!m) {
		return false;
	}

	updateMealFromIngredientItem(m.data(), item);

	if (m->save()) {
		Meal *md = new Meal(m.take(), this);
		m_data.append(md);
		connectSignals(md);
		emit itemsChanged();
		notifySumsChanged();
		return true;
	}
	return false;
}

void MealList::clearSelection()
{
	for (auto i : m_data) {
		i->setSelected(false);
	}
}

bool MealList::selectionToRecipe(qint32 nameIdx)
{
	QList<Meal *> sels;
	QList<int> idxs;

	QString name = "Rezept: " + processSelection(sels, idxs, nameIdx, true);

	if (sels.empty()) return false;

	QScopedPointer<RecipeDAO> r(m_facade->createRecipe());
	r->setName(name);
	QScopedPointer<IngredientItemList> lst(IngredientItemList::loadList(this, m_facade, r->ingredientListId()));

	for (auto m : sels) {
		lst->createItemFromMeal(m->data());
	}

	r->setReferenceServing(1);
	r->setDefaultServing(1);
	r->setFat(lst->sumFat());
	r->setProtein(lst->sumProtein());
	r->setCarbs(lst->sumCarbs());
	r->setCalories(lst->sumCalories());
	r->save();

	createMealForRecipe(r->id());

	// Back to front!
	for (auto i = idxs.rbegin(); i != idxs.rend(); ++i) {
		removeMeal(*i);
	}

	return true;
}

bool MealList::copySelection(qint32 nameIdx)
{
	QList<Meal *> sels;
	QList<int> idxs;

	QString name = "Rezept: " + processSelection(sels, idxs, nameIdx, true);

	if (sels.isEmpty()) return false;

	QString data;
	{
		QTextStream ts(&data);

		ts << name << ";1\n";
		for (auto *m : sels) {
			ts << m->name() << ';' << m->quantity() << ';' << m->fat() << ';' << m->carbs() << ';' << m->protein() << ';' << m->calories() << '\n';
		}
	}

	QGuiApplication::clipboard()->setText(data);
	return true;
}

bool MealList::recipeToIngredients(qint32 recipeIdx)
{
	clearSelection();
	if (recipeIdx < 0 || recipeIdx >= m_data.count())
		return false;

	if (!m_data[recipeIdx]->isConnectedToRecipe())
		return false;

	QScopedPointer<RecipeDAO> rec(m_facade->loadRecipe(m_data[recipeIdx]->recipeId()));
	QScopedPointer<IngredientItemList> lst(IngredientItemList::loadList(this, m_facade, rec->ingredientListId()));

	for (IngredientListItem *i : lst->ingredients()) {
		createIngredientFromListItem(i->data());
	}

	removeMeal(recipeIdx);

	return true;
}

bool MealList::importAsRecipe()
{
	QScopedPointer<RecipeDAO> r(m_facade->createRecipe());
	if (!r->save()) return false;

	QScopedPointer<Recipe> rec(new Recipe(r.take(), this));
	if (!rec->pasteFromClipboard()) {
		m_facade->removeRecipe(r->id());
		return false;
	}

	createMealForRecipe(rec->id());
	return true;
}

bool MealList::importAsIngredientList()
{
	ImportExportHelper::Header header;
	QList<ImportExportHelper::Item> itms;
	if (!ImportExportHelper::importData(QGuiApplication::clipboard()->text(), header, itms)) return false;

	for (auto i : itms) {
		MealDAO *m = m_facade->createMeal(m_date, m_type);
		m->setName(i.name);
		m->setQuantity(i.quantity);
		m->setFat(i.fat);
		m->setCarbs(i.carbs);
		m->setProtein(i.protein);
		m->setCalories(i.calories);

		if (m->save()) {
			Meal *md = new Meal(m, this);
			tryConnectMealToIngredientByName(md, UpdateField::None);
			m_data.append(md);
			connectSignals(md);
		} else {
			delete m;
		}
	}

	emit itemsChanged();
	notifySumsChanged();

	return true;
}

bool MealList::importAsSingleIngredient()
{
	ImportExportHelper::Header h;
	QList<ImportExportHelper::Item> itms;
	if (!ImportExportHelper::importData(QGuiApplication::clipboard()->text(), h, itms)) return false;

	// Might be overriden, or summed values
	// Just override the header's info if summed
	if (h.servings < 1) h.servings = 1;
	if (!h.isOverridden) {
		h.fat = h.carbs = h.protein = h.calories = 0.;
		for (auto i : itms) {
			h.fat += i.fat * i.quantity / h.servings;
			h.carbs += i.carbs * i.quantity / h.servings;
			h.protein += i.protein * i.quantity / h.servings;
			h.calories += i.calories * i.quantity / h.servings;
		}
	}

	MealDAO *m = m_facade->createMeal(m_date, m_type);
	m->setName(h.name);
	m->setQuantity(1);
	m->setFat(h.fat);
	m->setCarbs(h.carbs);
	m->setProtein(h.protein);
	m->setCalories(h.calories);

	if (m->save()) {
		Meal *md = new Meal(m, this);
		tryConnectMealToIngredientByName(md, UpdateField::None);
		m_data.append(md);
		connectSignals(md);
	} else {
		delete m;
	}

	emit itemsChanged();
	notifySumsChanged();

	return true;
}

QString MealList::processSelection(QList<Meal*> &sels, QList<int> &idxs, qint32 nameIdx, bool clear)
{
	QString name;
	for (int i = 0; i < m_data.count(); ++i) {
		if (m_data[i]->isSelected()) {
			sels << m_data[i];
			idxs << i;
			if (i == nameIdx) {
				name = m_data[i]->name();
			}
		}
	}

	if (clear)
		clearSelection();

	if (name.isEmpty() && !sels.empty()) {
		name = sels[0]->name();
	}

	return name;
}

qreal MealList::sumFat() const
{
	qreal sum = 0;
	for (auto m : m_data) {
		sum += m->calcFat();
	}
	return sum;
}

qreal MealList::sumProtein() const
{
	qreal sum = 0;
	for (auto m : m_data) {
		sum += m->calcProtein();
	}
	return sum;
}

qreal MealList::sumCarbs() const
{
	qreal sum = 0;
	for (auto m : m_data) {
		sum += m->calcCarbs();
	}
	return sum;
}

qreal MealList::sumCalories() const
{
	qreal sum = 0;
	for (auto m : m_data) {
		sum += m->calcCalories();
	}
	return sum;
}

bool MealList::isEmpty() const
{
	return m_data.isEmpty();
}

bool MealList::selectionEmpty() const
{
	for (auto i : m_data) {
		if (i->isSelected()) return false;
	}
	return true;
}

bool MealList::canImport(bool recheck)
{
	static bool s_canImport = ImportExportHelper::canImport(QGuiApplication::clipboard()->text());
	if (recheck) {
		bool newVal = ImportExportHelper::canImport(QGuiApplication::clipboard()->text());
		if (newVal != s_canImport) {
			s_canImport = newVal;
			emit canImportChanged();
		}
	}
	return s_canImport;
}

Meal *MealList::atFunc(QQmlListProperty<Meal> *p, int i)
{
    return static_cast<MealList *> (p->object)->m_data.at(i);
}

int MealList::countFunc(QQmlListProperty<Meal> *p)
{
    return static_cast<MealList*> (p->object)->m_data.count();
}

void MealList::connectSignals(Meal *m)
{
	connect(m, &Meal::fatChanged, this, &MealList::sumFatChanged);
	connect(m, &Meal::proteinChanged, this, &MealList::sumProteinChanged);
	connect(m, &Meal::carbsChanged, this, &MealList::sumCarbsChanged);
	connect(m, &Meal::caloriesChanged, this, &MealList::sumCaloriesChanged);
	connect(m, &Meal::isSelectedChanged, this, &MealList::selectionEmptyChanged);
}

void MealList::notifySumsChanged()
{
	emit sumFatChanged();
	emit sumProteinChanged();
	emit sumCarbsChanged();
	emit sumCaloriesChanged();
}

void MealList::updateMealFromIngredient(MealDAO *m, IngredientDAO *r, UpdateFields fields)
{
	if (fields.testFlag(UpdateField::Name)) m->setName(r->name());
	if (fields.testFlag(UpdateField::Quantity)) m->setQuantity(r->defaultQuantity());
	if (fields.testFlag(UpdateField::Id)) m->setIngredientId(r->id());
	if (fields.testFlag(UpdateField::Values)) {
		qint32 f = r->referenceQuantity() == 0 ? 1 : r->referenceQuantity();
		m->setFat(r->fat() / f);
		m->setProtein(r->protein() / f);
		m->setCarbs(r->carbs() / f);
		m->setCalories(r->calories() / f);
	}
}

void MealList::updateMealFromIngredientItem(MealDAO *m, const IngredientListItemDAO *r, UpdateFields fields)
{
	if (fields.testFlag(UpdateField::Name)) m->setName(r->name());
	if (fields.testFlag(UpdateField::Quantity)) m->setQuantity(r->quantity());
	if (fields.testFlag(UpdateField::Id)) m->setIngredientId(r->ingredientId());
	if (fields.testFlag(UpdateField::Values)) {
		m->setFat(r->fat());
		m->setProtein(r->protein());
		m->setCarbs(r->carbs());
		m->setCalories(r->calories());
	}
}

void MealList::updateMealFromRecipe(MealDAO *m, RecipeDAO *r, UpdateFields fields)
{
	if (fields.testFlag(UpdateField::Name)) m->setName(r->name());
	if (fields.testFlag(UpdateField::Quantity)) m->setQuantity(r->defaultServing());
	if (fields.testFlag(UpdateField::Id)) m->setRecipeId(r->id());
	if (fields.testFlag(UpdateField::Values)) {
		qint32 f = r->referenceServing() == 0 ? 1 : r->referenceServing();
		m->setFat(r->fat() / f);
		m->setProtein(r->protein() / f);
		m->setCarbs(r->carbs() / f);
		m->setCalories(r->calories() / f);
	}
}

bool MealList::tryConnectMealToIngredientByName(Meal *m, UpdateFields fields)
{
	QScopedPointer<IngredientDAO> r(m_facade->loadIngredientByName(m->name()));
	if (r.data()) {
		m->setIngredientId(r->id());
		updateMealFromIngredient(m->m_meal, r.data(), fields);
		return true;
	}
	return false;
}
