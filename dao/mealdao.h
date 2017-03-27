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

    virtual qreal factor() const = 0;
    virtual void setFactor(qreal fac) = 0;

    virtual qint32 fat() const = 0;
    virtual void setFat(qint32 f) = 0;

    qreal calcFat() const;
};

#endif // MEALDAO_H
