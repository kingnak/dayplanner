#include "mealdao.h"

MealDAO::MealDAO(qint32 id, DataBase *db)
    : DbDAOBase(db),
      m_id(id)
{

}

QString MealDAO::name() const
{
    return data<QString>("name");
}

void MealDAO::setName(const QString &name)
{
    setData("name", name);
}

MealDAO::Type MealDAO::type() const
{
    return static_cast<Type>(data<qint32>("type"));
}

void MealDAO::setType(MealDAO::Type t)
{
    setData("type", static_cast<qint32>(t));
}

QDate MealDAO::date() const
{
    return data<QDate>("date");
}

void MealDAO::setDate(QDate d)
{
    setData("date", d);
}

qreal MealDAO::factor() const
{
    return data<qreal>("factor");
}

void MealDAO::setFactor(qreal fac)
{
    setData("factor", fac);
}

qint32 MealDAO::fat() const
{
    return data<qint32>("fat");
}

void MealDAO::setFat(qint32 f)
{
    setData("fat", f);
}

qreal MealDAO::calcFat() const
{
    return static_cast<qreal>(fat()) * factor();
}
/*
QStringList MealDAO::keyFields()
{
    return QStringList() << "id";
}

QString MealDAO::keyData(const QString &field)
{
    if (field == "id") {
        return m_id;
    }
    Q_ASSERT(false);
    return "";
}
*/
QStringList MealDAO::orderFields()
{
    return QStringList() << "sort";
}

QString MealDAO::tableName()
{
    return "Meal";
}

bool MealDAO::isAutoId() const
{
    return true;
}

qint32 MealDAO::idValue() const
{
    return m_id;
}

void MealDAO::updateIdValue(qint32 id)
{
    m_id = id;
}
