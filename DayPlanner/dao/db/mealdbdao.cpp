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

qint32 MealDbDAO::fat() const
{
    return data<qint32>("fat");
}

void MealDbDAO::setFat(qint32 f)
{
    setData("fat", f);
}

qint32 MealDbDAO::protein() const
{
    return data<qint32>("protein");
}

void MealDbDAO::setProtein(qint32 p)
{
    setData("protein", p);
}

qint32 MealDbDAO::carbs() const
{
    return data<qint32>("carbs");
}

void MealDbDAO::setCarbs(qint32 c)
{
    setData("carbs", c);
}

qint32 MealDbDAO::calories() const
{
    return data<qint32>("calories");
}

void MealDbDAO::setCalories(qint32 c)
{
    setData("calories", c);
}

QStringList MealDbDAO::orderFields()
{
    return QStringList() << "sort";
}

QString MealDbDAO::tableName()
{
    return "Meal";
}

