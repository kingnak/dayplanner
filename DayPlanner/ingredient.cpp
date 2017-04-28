#include "ingredient.h"
#include "ingredientlist.h"

Ingredient::Ingredient(QObject *parent)
	: QObject(parent),
	  m_ingredient(nullptr)
{
	Q_ASSERT(false);
}

Ingredient::Ingredient(IngredientDAO *ingredient, QObject *parent)
	: QObject(parent),
	  m_ingredient(ingredient)
{

}

Ingredient::~Ingredient()
{
	delete m_ingredient;
}

qint32 Ingredient::id() const
{
	return m_ingredient->id();
}

QString Ingredient::name() const
{
	return m_ingredient->name();
}

void Ingredient::setName(const QString &n)
{
	if (n != name()) {
		m_ingredient->setName(n);
		emit nameChanged();
	}
}

qint32 Ingredient::referenceQuantity() const
{
	return m_ingredient->referenceQuantity();
}

void Ingredient::setReferenceQuantity(qint32 q)
{
	if (q != referenceQuantity()) {
		m_ingredient->setReferenceQuantity(q);
		emit referenceQuantityChanged();
	}
}

qint32 Ingredient::defaultQuantity() const
{
	return m_ingredient->defaultQuantity();
}

void Ingredient::setDefaultQuantity(qint32 q)
{
	if (q != defaultQuantity()) {
		m_ingredient->setDefaultQuantity(q);
		emit defaultQuantityChanged();
	}
}

qreal Ingredient::fat() const
{
	return m_ingredient->fat();
}

void Ingredient::setFat(qreal f)
{
	if (f != fat()) {
		m_ingredient->setFat(f);
		emit fatChanged();
	}
}

qreal Ingredient::protein() const
{
	return m_ingredient->protein();
}

void Ingredient::setProtein(qreal p)
{
	if (p != protein()) {
		m_ingredient->setProtein(p);
		emit proteinChanged();
	}
}

qreal Ingredient::carbs() const
{
	return m_ingredient->carbs();
}

void Ingredient::setCarbs(qreal c)
{
	if (c != carbs()) {
		m_ingredient->setCarbs(c);
		emit carbsChanged();
	}
}

qreal Ingredient::calories() const
{
	return m_ingredient->calories();
}

void Ingredient::setCalories(qreal c)
{
	if (c != calories()) {
		m_ingredient->setCalories(c);
		emit caloriesChanged();
	}
}

bool Ingredient::save()
{
	if (m_ingredient->save()) {
		IngredientNotifier::instance()->ingredientsChanged();
		return true;
	}
	return false;
}

bool Ingredient::reset()
{
	if (m_ingredient->load()) {
		emit nameChanged();
		emit fatChanged();
		emit proteinChanged();
		emit carbsChanged();
		emit caloriesChanged();
		return true;
	}
	return false;
}

void Ingredient::calcTo100()
{
	qint32 f = m_ingredient->referenceQuantity() == 0 ? 100 : m_ingredient->referenceQuantity();
	setFat(fat()*100.0/f);
	setProtein(protein()*100.0/f);
	setCarbs(carbs()*100.0/f);
	setCalories(calories()*100.0/f);
	setReferenceQuantity(100);
}
