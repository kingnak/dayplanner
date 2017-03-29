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

    virtual qint32 quantity() const;
    virtual void setQuantity(qint32 q);

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

    DAO_USE(DbAutoIdDAOBase)

protected:
    virtual QStringList orderFields();
    virtual QString tableName();
};

#endif // RECIPEDBDAO_H
