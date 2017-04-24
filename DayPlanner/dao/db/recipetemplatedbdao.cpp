#include "recipetemplatedbdao.h"

RecipeTemplateDbDAO::RecipeTemplateDbDAO(qint32 id, DataBase *db)
	: DbAutoIdDAOBase(db, id)
{
	load();
}

qint32 RecipeTemplateDbDAO::id() const
{
	return DbAutoIdDAOBase::id();
}

QString RecipeTemplateDbDAO::name() const
{
	return data<QString>("name");
}

void RecipeTemplateDbDAO::setName(const QString &n)
{
	setData("name", n);
}

qint32 RecipeTemplateDbDAO::referenceServing() const
{
	return data<qint32>("refServing");
}

void RecipeTemplateDbDAO::setReferenceServing(qint32 q)
{
	setData("refServing", q);
}

qint32 RecipeTemplateDbDAO::defaultServing() const
{
	return data<qint32>("defaulServing");
}

void RecipeTemplateDbDAO::setDefaultServing(qint32 q)
{
	setData("defaultServing", q);
}

qreal RecipeTemplateDbDAO::fat() const
{
	return data<qreal>("fat");
}

void RecipeTemplateDbDAO::setFat(qreal f)
{
	setData("fat", f);
}

qreal RecipeTemplateDbDAO::protein() const
{
	return data<qreal>("protein");
}

void RecipeTemplateDbDAO::setProtein(qreal p)
{
	setData("protein", p);
}

qreal RecipeTemplateDbDAO::carbs() const
{
	return data<qreal>("carbs");
}

void RecipeTemplateDbDAO::setCarbs(qreal c)
{
	setData("carbs", c);
}

qreal RecipeTemplateDbDAO::calories() const
{
	return data<qreal>("calories");
}

void RecipeTemplateDbDAO::setCalories(qreal c)
{
	setData("calories", c);
}

QString RecipeTemplateDbDAO::url() const
{
	return data<QString>("url");
}

void RecipeTemplateDbDAO::setUrl(const QString &u)
{
	setData("url", u);
}

QString RecipeTemplateDbDAO::note() const
{
	return data<QString>("note");
}

void RecipeTemplateDbDAO::setNote(const QString &n)
{
	setData("note", n);
}

qint32 RecipeTemplateDbDAO::ingredientListId() const
{
	return data<qint32>("ingredientListId");
}

void RecipeTemplateDbDAO::setIngredientListId(qint32 id)
{
	setData("ingredientListId", id);
}

QStringList RecipeTemplateDbDAO::orderFields()
{
	return QStringList() << "name";
}

QString RecipeTemplateDbDAO::tableName()
{
	return "RecipeTemplate";
}
