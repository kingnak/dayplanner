#ifndef RECIPEDAO_H
#define RECIPEDAO_H

#include "daobase.h"
#include <QString>

class RecipeDAO : public virtual DAOBase
{
public:
	virtual qint32 id() const = 0;

	virtual QString name() const = 0;
	virtual void setName(const QString &n) = 0;

	virtual qint32 referenceServing() const = 0;
	virtual void setReferenceServing(qint32 q) = 0;

	virtual qint32 defaultServing() const = 0;
	virtual void setDefaultServing(qint32 q) = 0;

	virtual qreal fat() const = 0;
	virtual void setFat(qreal f) = 0;

	virtual qreal protein() const = 0;
	virtual void setProtein(qreal p) = 0;

	virtual qreal carbs() const = 0;
	virtual void setCarbs(qreal c) = 0;

	virtual qreal calories() const = 0;
	virtual void setCalories(qreal c) = 0;

	virtual QString url() const = 0;
	virtual void setUrl(const QString &u) = 0;

	virtual QString note() const = 0;
	virtual void setNote(const QString &n) = 0;

	virtual qint32 ingredientListId() const = 0;
	virtual void setIngredientListId(qint32 id) = 0;

	virtual bool nutritionValuesOverridden() const = 0;
	virtual void setNutritionValuesOverridden(bool o) = 0;

	virtual qint32 templateId() const = 0;
	virtual void setTemplateId(qint32 id) = 0;
};

#endif // RECIPEDAO_H
