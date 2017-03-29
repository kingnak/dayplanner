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
    }

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
        m_data.append(new Meal(m, this));
        emit itemsChanged();
    } else {
        delete m;
    }
}

void MealList::createMealForRecipe(qint32 recipeId)
{
    if (recipeId < 0) {
        return;
    }

    MealDAO *m = m_facade->createMeal(m_date, m_type);
    if (!m) {
        return;
    }

    RecipeDAO *r = m_facade->loadRecipe(recipeId);
    if (!r) {
        return;
    }
    if (r->state() == DAOBase::State::New) {
        delete r;
        return;
    }

    m->setName(r->name());
    m->setFactor(r->quantity());
    m->setFat(r->fat());
    m->setProtein(r->protein());
    m->setCarbs(r->carbs());
    m->setCalories(r->calories());
    m->setRecipeId(r->id());

    delete r;
    r = nullptr;

    if (m->save()) {
        m_data.append(new Meal(m, this));
        emit itemsChanged();
    } else {
        delete m;
    }
}

void MealList::removeMeal(qint32 idx)
{
    if (idx < 0 || idx >= m_data.count()) {
        return;
    }

    m_data.takeAt(idx)->deleteLater();
    emit itemsChanged();
}

Meal *MealList::atFunc(QQmlListProperty<Meal> *p, int i)
{
    return static_cast<MealList *> (p->object)->m_data.at(i);
}

int MealList::countFunc(QQmlListProperty<Meal> *p)
{
    return static_cast<MealList*> (p->object)->m_data.count();
}
