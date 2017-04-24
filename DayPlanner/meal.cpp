#include "meal.h"
#include "dao/mealdao.h"
#include <QLocale>

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

bool Meal::erase()
{
    return m_meal->remove();
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
			emit nameChanged();
        }
    }
}

qreal Meal::factor() const
{
    qreal f = m_meal->factor();
    if (qFuzzyIsNull(f)) return 1;
    return f;
}

void Meal::setFactor(qreal f)
{
    if (f != factor()) {
        m_meal->setFactor(f);
        if (m_meal->save()) {
			notifyValuesChanged();
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

qreal Meal::calcFat() const
{
	return fat() * factor();
}

void Meal::updateFat(qreal f)
{
	setFat(f / factor());
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

qreal Meal::calcProtein() const
{
	return protein() * factor();
}

void Meal::updateProtein(qreal p)
{
	setProtein(p / factor());
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

qreal Meal::calcCarbs() const
{
	return carbs() * factor();
}

void Meal::updateCarbs(qreal c)
{
	setCarbs(c / factor());
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

qreal Meal::calcCalories() const
{
	return calories() * factor();
}

void Meal::updateCalories(qreal c)
{
	setCalories(c / factor());
}

qint32 Meal::ingredientId() const
{
	return m_meal->ingredientId();
}

void Meal::setIngredientId(qint32 id)
{
	if (id != ingredientId()) {
		m_meal->setIngredientId(id);
		if (m_meal->save()) {
			emit ingredientIdChanged();
		}
	}
}

bool Meal::isConnectedToIngredient() const
{
	return ingredientId() != DAOBase::NoItemIndex;
}

void Meal::notifyValuesChanged()
{
	emit nameChanged();
	emit factorChanged();
	emit fatChanged();
	emit proteinChanged();
	emit carbsChanged();
	emit caloriesChanged();
}
