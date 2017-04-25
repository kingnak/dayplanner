#ifndef MEALDAO_H
#define MEALDAO_H

#include "daobase.h"
#include <QDate>

class MealDAO : public virtual DAOBase
{
public:
    virtual QString name() const = 0;
    virtual void setName(const QString &name) = 0;

    virtual qint32 type() const = 0;
    virtual void setType(qint32 t) = 0;

    virtual QDate date() const = 0;
    virtual void setDate(QDate d) = 0;

    virtual qreal quantity() const = 0;
    virtual void setQuantity(qreal fac) = 0;

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

	virtual qint32 recipeId() const = 0;
	virtual void setRecipeId(qint32 id) = 0;
};

#endif // MEALDAO_H
