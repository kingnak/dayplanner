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

qint32 RecipeDbDAO::referenceServing() const
{
	return data<qint32>("refServing");
}

void RecipeDbDAO::setReferenceServing(qint32 q)
{
	setData("refServing", q);
}

qint32 RecipeDbDAO::defaultServing() const
{
	return data<qint32>("defaulServing");
}

void RecipeDbDAO::setDefaultServing(qint32 q)
{
	setData("defaultServing", q);
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

QString RecipeDbDAO::note() const
{
	return data<QString>("note");
}

void RecipeDbDAO::setNote(const QString &n)
{
	setData("note", n);
}

qint32 RecipeDbDAO::ingredientListId() const
{
	return data<qint32>("ingredientListId");
}

void RecipeDbDAO::setIngredientListId(qint32 id)
{
	setData("ingredientListId", id);
}

bool RecipeDbDAO::nutritionValuesOverridden() const
{
	return data<qint32>("overridden") != 0;
}

void RecipeDbDAO::setNutritionValuesOverridden(bool o)
{
	setData<qint32>("overridden", o ? 1 : 0);
}

qint32 RecipeDbDAO::templateId() const
{
	return data<qint32>("templateId");
}

void RecipeDbDAO::setTemplateId(qint32 id)
{
	setData("templateId", id);
}

QStringList RecipeDbDAO::orderFields()
{
	return QStringList() << "name";
}

QString RecipeDbDAO::tableName()
{
	return "Recipe";
}
