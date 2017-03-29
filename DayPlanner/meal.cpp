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

qreal Meal::factor() const
{
    return m_meal->factor();
}

void Meal::setFactor(qreal f)
{
    if (f != factor()) {
        m_meal->setFactor(f);
        if (m_meal->save()) {
            emit factorChanged();
            emit fatChanged();
            emit proteinChanged();
            emit carbsChanged();
            emit caloriesChanged();
        }
    }
}

qreal Meal::fat() const
{
    return m_meal->fat();
}

void Meal::setFat(qreal f)
{
    if (f != fat()) {
        m_meal->setFat(f);
        if (m_meal->save()) {
            emit fatChanged();
        }
    }
}

void Meal::updateFat(qreal f)
{
    setFat(f/factor());
}

qreal Meal::protein() const
{
    return m_meal->protein();
}

void Meal::setProtein(qreal p)
{
    if (p != protein()) {
        m_meal->setProtein(p);
        if (m_meal->save()) {
            emit proteinChanged();
        }
    }
}

void Meal::updateProtein(qreal p)
{
    setProtein(p/factor());
}

qreal Meal::carbs() const
{
    return m_meal->carbs();
}

void Meal::setCarbs(qreal c)
{
    if (c != carbs()) {
        m_meal->setCarbs(c);
        if (m_meal->save()) {
            emit carbsChanged();
        }
    }
}

void Meal::updateCarbs(qreal c)
{
    setCarbs(c/factor());
}

qreal Meal::calories() const
{
    return m_meal->calories();
}

void Meal::setCalories(qreal c)
{
    if (c != calories()) {
        m_meal->setCalories(c);
        if (m_meal->save()) {
            emit caloriesChanged();
        }
    }
}

void Meal::updateCalories(qreal c)
{
    setCalories(c/factor());
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
