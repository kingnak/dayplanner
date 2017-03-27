#include "meal.h"
#include "dao/mealdao.h"

Meal::Meal(QObject *parent)
    : QObject(parent),
      m_meal(nullptr)
{
    Q_ASSERT(false);
}

Meal::Meal(MealDAO *meal, QObject *parent)
    : QObject(parent),
      m_meal(meal)
{
}

Meal::~Meal()
{
    delete m_meal;
}

Meal::Type Meal::type() const
{
    return static_cast<Type> (m_meal->type());
}

QString Meal::name() const
{
    return m_meal->name();
}

void Meal::setName(const QString &n)
{
    if (n != name()) {
        m_meal->setName(n);
        if (m_meal->save()) {
            emit nameChanged(n);
        }
    }
}

qint32 Meal::fat() const
{
    return m_meal->fat();
}

void Meal::setFat(const qint32 f)
{
    if (f != fat()) {
        m_meal->setFat(f);
        if (m_meal->save()) {
            emit fatChanged();
        }
    }
}

qint32 Meal::protein() const
{
    return m_meal->protein();
}

void Meal::setProtein(const qint32 p)
{
    if (p != protein()) {
        m_meal->setProtein(p);
        if (m_meal->save()) {
            emit proteinChanged();
        }
    }
}

qint32 Meal::carbs() const
{
    return m_meal->carbs();
}

void Meal::setCarbs(qint32 c)
{
    if (c != carbs()) {
        m_meal->setCarbs(c);
        if (m_meal->save()) {
            emit carbsChanged();
        }
    }
}

qint32 Meal::calories() const
{
    return m_meal->calories();
}

void Meal::setCalories(qint32 c)
{
    if (c != calories()) {
        m_meal->setCalories(c);
        if (m_meal->save()) {
            emit caloriesChanged();
        }
    }
}

qreal Meal::calcFat() const
{
    return m_meal->fat() * m_meal->factor();
}

qreal Meal::calcProtein() const
{
    return m_meal->protein() * m_meal->factor();
}

qreal Meal::calcCarbs() const
{
    return m_meal->carbs() * m_meal->factor();
}

qreal Meal::calcCalories() const
{
    return m_meal->calories() * m_meal->factor();
}
