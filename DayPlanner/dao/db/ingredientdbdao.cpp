#include "ingredientdbdao.h"

IngredientDbDAO::IngredientDbDAO(qint32 id, DataBase *db)
    : DbAutoIdDAOBase(db, id)
{
    load();
}

qint32 IngredientDbDAO::id() const
{
    return DbAutoIdDAOBase::id();
}

QString IngredientDbDAO::name() const
{
    return data<QString>("name");
}

void IngredientDbDAO::setName(const QString &n)
{
    setData("name", n);
}

qint32 IngredientDbDAO::quantity() const
{
    return data<qint32>("quantity");
}

void IngredientDbDAO::setQuantity(qint32 q)
{
    setData("quantity", q);
}

qreal IngredientDbDAO::fat() const
{
    return data<qreal>("fat");
}

void IngredientDbDAO::setFat(qreal f)
{
    setData("fat", f);
}

qreal IngredientDbDAO::protein() const
{
    return data<qreal>("protein");
}

void IngredientDbDAO::setProtein(qreal p)
{
    setData("protein", p);
}

qreal IngredientDbDAO::carbs() const
{
    return data<qreal>("carbs");
}

void IngredientDbDAO::setCarbs(qreal c)
{
    setData("carbs", c);
}

qreal IngredientDbDAO::calories() const
{
    return data<qreal>("calories");
}

void IngredientDbDAO::setCalories(qreal c)
{
    setData("calories", c);
}

QString IngredientDbDAO::url() const
{
    return data<QString>("url");
}

void IngredientDbDAO::setUrl(const QString &u)
{
    setData("url", u);
}

QStringList IngredientDbDAO::orderFields()
{
    return QStringList() << "name";
}

QString IngredientDbDAO::tableName()
{
    return "Ingredient";
}
