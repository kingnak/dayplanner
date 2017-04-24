#include "meallist.h"
#include "dao/dao.h"
#include "meal.h"
#include "dao/ingredientdao.h"
#include "ingredientlist.h"
#include "dao/recipedao.h"
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

	r->setDefaultQuantity(qFuzzyIsNull(m->factor()) ? 1 : m->factor());
	r->setReferenceQuantity(100);
	qreal f = qreal(r->defaultQuantity())/r->referenceQuantity();
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
	if (fields.testFlag(UpdateField::Quantity)) m->setFactor(r->defaultQuantity());
	if (fields.testFlag(UpdateField::Id)) m->setIngredientId(r->id());
	if (fields.testFlag(UpdateField::Values)) {
		qreal f = r->referenceQuantity() == 0 ? 1 : r->referenceQuantity();
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
