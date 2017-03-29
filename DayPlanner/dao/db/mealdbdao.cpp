#include "mealdbdao.h"

MealDbDAO::MealDbDAO(qint32 id, DataBase *db)
    : DbAutoIdDAOBase(db, id)
{
    load();
}

qint32 MealDbDAO::sort() const
{
    return data<qint32>("sort");
}

void MealDbDAO::setSort(qint32 sort)
{
    setData("sort", sort);
}

QString MealDbDAO::name() const
{
    return data<QString>("name");
}

void MealDbDAO::setName(const QString &name)
{
    setData("name", name);
}

qint32 MealDbDAO::type() const
{
    return data<qint32>("type");
}

void MealDbDAO::setType(qint32 t)
{
    setData("type", t);
}

QDate MealDbDAO::date() const
{
    return data<QDate>("date");
}

void MealDbDAO::setDate(QDate d)
{
    setData("date", d);
}

qreal MealDbDAO::factor() const
{
    return data<qreal>("factor");
}

void MealDbDAO::setFactor(qreal fac)
{
    setData("factor", fac);
}

qreal MealDbDAO::fat() const
{
    return data<qreal>("fat");
}

void MealDbDAO::setFat(qreal f)
{
    setData("fat", f);
}

qreal MealDbDAO::protein() const
{
    return data<qreal>("protein");
}

void MealDbDAO::setProtein(qreal p)
{
    setData("protein", p);
}

qreal MealDbDAO::carbs() const
{
    return data<qreal>("carbs");
}

void MealDbDAO::setCarbs(qreal c)
{
    setData("carbs", c);
}

qreal MealDbDAO::calories() const
{
    return data<qreal>("calories");
}

void MealDbDAO::setCalories(qreal c)
{
    setData("calories", c);
}

qint32 MealDbDAO::recipeId() const
{
    return data<qint32>("recipeId");
}

void MealDbDAO::setRecipeId(qint32 id)
{
    setData("recipeId", id);
}

QStringList MealDbDAO::orderFields()
{
    return QStringList() << "sort";
}

QString MealDbDAO::tableName()
{
    return "Meal";
}

