#include "meallist.h"
#include "dao/dao.h"
#include "meal.h"
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
    return QQmlListProperty<Meal> (this, nullptr, MealList::countFunc, MealList::atFunc);
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

    qreal f = qMax(r->quantity(), 1);
    m->setName(r->name());
    m->setFactor(f);
    m->setFat(r->fat() / f);
    m->setProtein(r->protein() / f);
    m->setCarbs(r->carbs() / f);
    m->setCalories(r->calories() / f);
    m->setRecipeId(r->id());

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

QString MealList::sumFat() const
{
	qreal sum = 0;
	for (auto m : m_data) {
		sum += m->calcFat();
	}
	return Meal::formatNumber(sum);
}

QString MealList::sumProtein() const
{
	qreal sum = 0;
	for (auto m : m_data) {
		sum += m->calcProtein();
	}
	return Meal::formatNumber(sum);
}

QString MealList::sumCarbs() const
{
	qreal sum = 0;
	for (auto m : m_data) {
		sum += m->calcCarbs();
	}
	return Meal::formatNumber(sum);
}

QString MealList::sumCalories() const
{
	qreal sum = 0;
	for (auto m : m_data) {
		sum += m->calcCalories();
	}
	return Meal::formatNumber(sum);
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
