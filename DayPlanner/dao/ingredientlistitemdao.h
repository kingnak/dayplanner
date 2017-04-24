#ifndef INGREDIENTLISTITEMDAO_H
#define INGREDIENTLISTITEMDAO_H

#include "daobase.h"
#include <QString>

class IngredientListItemDAO : public virtual DAOBase
{
public:
	virtual qint32 id() const = 0;

	virtual QString name() const = 0;
	virtual void setName(const QString &name) = 0;

	virtual qreal factor() const = 0;
	virtual void setFactor(qreal fac) = 0;

	virtual qreal fat() const = 0;
	virtual void setFat(qreal f) = 0;

	virtual qreal protein() const = 0;
	virtual void setProtein(qreal p) = 0;

	virtual qreal carbs() const = 0;
	virtual void setCarbs(qreal c) = 0;

	virtual qreal calories() const = 0;
	virtual void setCalories(qreal c) = 0;

	virtual qint32 ingredientId() const = 0;
	virtual void setIngredientId(qint32 id) = 0;
};

#endif // INGREDIENTLISTITEMDAO_H
