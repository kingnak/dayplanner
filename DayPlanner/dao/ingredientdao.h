#ifndef INGREDIENTDAO_H
#define INGREDIENTDAO_H

#include "daobase.h"
#include <QString>

class IngredientDAO : public virtual DAOBase
{
public:
    virtual qint32 id() const = 0;

    virtual QString name() const = 0;
    virtual void setName(const QString &n) = 0;

    virtual qint32 quantity() const = 0;
    virtual void setQuantity(qint32 q) = 0;

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
};

#endif // INGREDIENTDAO_H
