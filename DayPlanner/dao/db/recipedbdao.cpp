#include "recipedbdao.h"

RecipeDbDAO::RecipeDbDAO(qint32 id, DataBase *db)
    : DbAutoIdDAOBase(db, id)
{
    load();
}

qint32 RecipeDbDAO::id() const
{
    return DbAutoIdDAOBase::id();
}

QString RecipeDbDAO::name() const
{
    return data<QString>("name");
}

void RecipeDbDAO::setName(const QString &n)
{
    setData("name", n);
}

qint32 RecipeDbDAO::quantity() const
{
    return data<qint32>("quantity");
}

void RecipeDbDAO::setQuantity(qint32 q)
{
    setData("quantity", q);
}

qreal RecipeDbDAO::fat() const
{
    return data<qreal>("fat");
}

void RecipeDbDAO::setFat(qreal f)
{
    setData("fat", f);
}

qreal RecipeDbDAO::protein() const
{
    return data<qreal>("protein");
}

void RecipeDbDAO::setProtein(qreal p)
{
    setData("protein", p);
}

qreal RecipeDbDAO::carbs() const
{
    return data<qreal>("carbs");
}

void RecipeDbDAO::setCarbs(qreal c)
{
    setData("carbs", c);
}

qreal RecipeDbDAO::calories() const
{
    return data<qreal>("calories");
}

void RecipeDbDAO::setCalories(qreal c)
{
    setData("calories", c);
}

QString RecipeDbDAO::url() const
{
    return data<QString>("url");
}

void RecipeDbDAO::setUrl(const QString &u)
{
    setData("url", u);
}

QStringList RecipeDbDAO::orderFields()
{
    return QStringList() << "name";
}

QString RecipeDbDAO::tableName()
{
    return "Recipe";
}
