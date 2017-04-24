#include "ingredientlistitem.h"

IngredientListItem::IngredientListItem(QObject *parent)
	: QObject(parent),
	  m_item(nullptr)
{
	Q_ASSERT(false);
}

IngredientListItem::IngredientListItem(IngredientListItemDAO *item, QObject *parent)
	: QObject(parent),
	  m_item(item)
{
}

IngredientListItem::~IngredientListItem()
{
	delete m_item;
}


bool IngredientListItem::erase()
{
	return m_item->remove();
}

QString IngredientListItem::name() const
{
	return m_item->name();
}

void IngredientListItem::setName(const QString &n)
{
	if (n != name()) {
		m_item->setName(n);
		if (m_item->save()) {
			emit nameChanged();
		}
	}
}

qreal IngredientListItem::factor() const
{
	qreal f = m_item->factor();
	if (qFuzzyIsNull(f)) return 1;
	return f;
}

void IngredientListItem::setFactor(qreal f)
{
	if (f != factor()) {
		m_item->setFactor(f);
		if (m_item->save()) {
			notifyValuesChanged();
		}
	}
}

qreal IngredientListItem::fat() const
{
	return m_item->fat();
}

void IngredientListItem::setFat(qreal f)
{
	if (f != fat()) {
		m_item->setFat(f);
		if (m_item->save()) {
			emit fatChanged();
		}
	}
}

qreal IngredientListItem::calcFat() const
{
	return fat() * factor();
}

void IngredientListItem::updateFat(qreal f)
{
	setFat(f / factor());
}

qreal IngredientListItem::protein() const
{
	return m_item->protein();
}

void IngredientListItem::setProtein(qreal p)
{
	if (p != protein()) {
		m_item->setProtein(p);
		if (m_item->save()) {
			emit proteinChanged();
		}
	}
}

qreal IngredientListItem::calcProtein() const
{
	return protein() * factor();
}

void IngredientListItem::updateProtein(qreal p)
{
	setProtein(p / factor());
}

qreal IngredientListItem::carbs() const
{
	return m_item->carbs();
}

void IngredientListItem::setCarbs(qreal c)
{
	if (c != carbs()) {
		m_item->setCarbs(c);
		if (m_item->save()) {
			emit carbsChanged();
		}
	}
}

qreal IngredientListItem::calcCarbs() const
{
	return carbs() * factor();
}

void IngredientListItem::updateCarbs(qreal c)
{
	setCarbs(c / factor());
}

qreal IngredientListItem::calories() const
{
	return m_item->calories();
}

void IngredientListItem::setCalories(qreal c)
{
	if (c != calories()) {
		m_item->setCalories(c);
		if (m_item->save()) {
			emit caloriesChanged();
		}
	}
}

qreal IngredientListItem::calcCalories() const
{
	return calories() * factor();
}

void IngredientListItem::updateCalories(qreal c)
{
	setCalories(c / factor());
}

qint32 IngredientListItem::ingredientId() const
{
	return m_item->ingredientId();
}

void IngredientListItem::setIngredientId(qint32 id)
{
	if (id != ingredientId()) {
		m_item->setIngredientId(id);
		if (m_item->save()) {
			emit ingredientIdChanged();
		}
	}
}

bool IngredientListItem::isConnectedToIngredient() const
{
	return ingredientId() != DAOBase::NoItemIndex;
}

void IngredientListItem::notifyValuesChanged()
{
	emit nameChanged();
	emit factorChanged();
	emit fatChanged();
	emit proteinChanged();
	emit carbsChanged();
	emit caloriesChanged();
}
