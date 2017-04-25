#include "ingredientlistitemdbdao.h"


IngredientListItemDbDAO::IngredientListItemDbDAO(qint32 id, DataBase *db)
	: DbAutoIdDAOBase(db, id)
{
	load();
}

qint32 IngredientListItemDbDAO::id() const
{
	return DbAutoIdDAOBase::id();
}

qint32 IngredientListItemDbDAO::sort() const
{
	return data<qint32>("sort");
}

void IngredientListItemDbDAO::setSort(qint32 sort)
{
	setData("sort", sort);
}

QString IngredientListItemDbDAO::name() const
{
	return data<QString>("name");
}

void IngredientListItemDbDAO::setName(const QString &name)
{
	setData("name", name);
}

qreal IngredientListItemDbDAO::quantity() const
{
	return data<qreal>("quantity");
}

void IngredientListItemDbDAO::setQuantity(qreal q)
{
	setData("quantity", q);
}

qreal IngredientListItemDbDAO::fat() const
{
	return data<qreal>("fat");
}

void IngredientListItemDbDAO::setFat(qreal f)
{
	setData("fat", f);
}

qreal IngredientListItemDbDAO::protein() const
{
	return data<qreal>("protein");
}

void IngredientListItemDbDAO::setProtein(qreal p)
{
	setData("protein", p);
}

qreal IngredientListItemDbDAO::carbs() const
{
	return data<qreal>("carbs");
}

void IngredientListItemDbDAO::setCarbs(qreal c)
{
	setData("carbs", c);
}

qreal IngredientListItemDbDAO::calories() const
{
	return data<qreal>("calories");
}

void IngredientListItemDbDAO::setCalories(qreal c)
{
	setData("calories", c);
}

qint32 IngredientListItemDbDAO::ingredientId() const
{
	return data<qint32>("ingredientId");
}

void IngredientListItemDbDAO::setIngredientId(qint32 id)
{
	setData("ingredientId", id);
}

QStringList IngredientListItemDbDAO::orderFields()
{
	return QStringList() << "sort";
}

QString IngredientListItemDbDAO::tableName()
{
	return "IngredientListItem";
}


