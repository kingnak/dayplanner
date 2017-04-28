#ifndef INGREDIENTDBDAO_H
#define INGREDIENTDBDAO_H

#include "dbautoiddaobase.h"
#include "../ingredientdao.h"

class IngredientDbDAO : public IngredientDAO, private DbAutoIdDAOBase
{
public:
    IngredientDbDAO(qint32 id, DataBase *db);

    virtual qint32 id() const;

    virtual QString name() const;
    virtual void setName(const QString &n);

	virtual qint32 referenceQuantity() const;
	virtual void setReferenceQuantity(qint32 q);

	virtual qint32 defaultQuantity() const;
	virtual void setDefaultQuantity(qint32 q);

    virtual qreal fat() const;
    virtual void setFat(qreal f);

    virtual qreal protein() const;
    virtual void setProtein(qreal p);

    virtual qreal carbs() const;
    virtual void setCarbs(qreal c);

    virtual qreal calories() const;
    virtual void setCalories(qreal c);

protected:
    virtual QStringList orderFields();
    virtual QString tableName();
};

#endif // INGREDIENTDBDAO_H
