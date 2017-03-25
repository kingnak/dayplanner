#ifndef MEALDAO_H
#define MEALDAO_H

#include "dbdaobase.h"
#include <QDate>

class MealDAO : public DbDAOBase
{
public:
    enum Type {
        Breakfast = 1,
        Lunch,
        Dinner,
        Snacks,
        Other
    };

    MealDAO(qint32 id, DataBase *db);

    qint32 id() const { return m_id; }
    //void setId(qint32 id);

    QString name() const;
    void setName(const QString &name);

    Type type() const;
    void setType(Type t);

    QDate date() const;
    void setDate(QDate d);

    qreal factor() const;
    void setFactor(qreal fac);

    qint32 fat() const;
    void setFat(qint32 f);

    qreal calcFat() const;

protected:
    //virtual QStringList keyFields();
    //virtual QString keyData(const QString &field);
    virtual QStringList orderFields();
    virtual QString tableName();

    virtual bool isAutoId() const;
    virtual qint32 idValue() const;
    virtual void updateIdValue(qint32 id);

private:
    qint32 m_id;
};

#endif // MEALDAO_H
