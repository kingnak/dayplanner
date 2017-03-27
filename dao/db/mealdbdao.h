#ifndef MEALDBDAO_H
#define MEALDBDAO_H

#include "../mealdao.h"
#include "dbautoiddaobase.h"

class MealDbDAO : public MealDAO, private DbAutoIdDAOBase
{
public:
    MealDbDAO(qint32 id, DataBase *db);

    QString name() const;
    void setName(const QString &name);

    qint32 type() const;
    void setType(qint32 t);

    QDate date() const;
    void setDate(QDate d);

    qreal factor() const;
    void setFactor(qreal fac);

    qint32 fat() const;
    void setFat(qint32 f);

    qreal calcFat() const;

    qint32 sort() const;
    void setSort(qint32 sort);

    DAO_USE(DbAutoIdDAOBase)

protected:
    virtual QStringList orderFields();
    virtual QString tableName();
};

#endif // MEALDBDAO_H
