#ifndef RECIPEDBDAO_H
#define RECIPEDBDAO_H

#include "dbautoiddaobase.h"
#include "../recipedao.h"

class RecipeDbDAO : public RecipeDAO, private DbAutoIdDAOBase
{
public:
	RecipeDbDAO(qint32 id, DataBase *db);

	virtual qint32 id() const;

	virtual QString name() const;
	virtual void setName(const QString &n);

	virtual qint32 referenceServing() const;
	virtual void setReferenceServing(qint32 q);

	virtual qint32 defaultServing() const;
	virtual void setDefaultServing(qint32 q);

	virtual qreal fat() const;
	virtual void setFat(qreal f);

	virtual qreal protein() const;
	virtual void setProtein(qreal p);

	virtual qreal carbs() const;
	virtual void setCarbs(qreal c);

	virtual qreal calories() const;
	virtual void setCalories(qreal c);

	virtual QString url() const;
	virtual void setUrl(const QString &u);

	virtual QString note() const;
	virtual void setNote(const QString &n);

	virtual qint32 ingredientListId() const;
	virtual void setIngredientListId(qint32 id);

	virtual bool nutritionValuesOverridden() const;
	virtual void setNutritionValuesOverridden(bool o);

	virtual qint32 templateId() const;
	virtual void setTemplateId(qint32 id);

	DAO_USE(DbAutoIdDAOBase)

protected:
	virtual QStringList orderFields();
	virtual QString tableName();
};

#endif // RECIPEDBDAO_H
