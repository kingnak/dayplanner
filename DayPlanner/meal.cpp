#include "meal.h"
#include "dao/mealdao.h"
#include "dao/dao.h"
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
	if (isConnectedToRecipe()) {
		globalDAOFacade()->removeRecipe(m_meal->recipeId());
	}
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

qint32 Meal::quantity() const
{
	qint32 f = m_meal->quantity();
	if (f == 0) return 1;
    return f;
}

void Meal::setQuantity(qint32 f)
{
    if (f != quantity()) {
        m_meal->setQuantity(f);
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
	return fat() * quantity();
}

void Meal::updateFat(qreal f)
{
	setFat(f / quantity());
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
	return protein() * quantity();
}

void Meal::updateProtein(qreal p)
{
	setProtein(p / quantity());
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
	return carbs() * quantity();
}

void Meal::updateCarbs(qreal c)
{
	setCarbs(c / quantity());
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
	return calories() * quantity();
}

void Meal::updateCalories(qreal c)
{
	setCalories(c / quantity());
}

qint32 Meal::ingredientId() const
{
	return m_meal->ingredientId();
}

void Meal::setIngredientId(qint32 id)
{
	Q_ASSERT(!isConnected());
	if (id != ingredientId()) {
		m_meal->setIngredientId(id);
		if (m_meal->save()) {
			emit ingredientIdChanged();
			emit connectedChanged();
		}
	}
}

bool Meal::isConnectedToIngredient() const
{
	return ingredientId() != DAOBase::NoItemIndex;
}

qint32 Meal::recipeId() const
{
	return m_meal->recipeId();
}

void Meal::setRecipeId(qint32 id)
{
	Q_ASSERT(!isConnected());
	if (id != recipeId()) {
		m_meal->setRecipeId(id);
		if (m_meal->save()) {
			emit recipeIdChanged();
			emit connectedChanged();
		}
	}
}

bool Meal::isConnectedToRecipe() const
{
	return recipeId() != DAOBase::NoItemIndex;
}

bool Meal::isConnected() const
{
	return isConnectedToIngredient() || isConnectedToRecipe();
}

void Meal::notifyValuesChanged()
{
	emit nameChanged();
	emit quantityChanged();
	emit fatChanged();
	emit proteinChanged();
	emit carbsChanged();
	emit caloriesChanged();
}
