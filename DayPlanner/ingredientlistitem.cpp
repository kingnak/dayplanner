#include "ingredientlistitem.h"

IngredientListItem::IngredientListItem(QObject *parent)
	: QObject(parent),
	  m_item(nullptr),
	  m_mult(1)
{
	Q_ASSERT(false);
}

IngredientListItem::IngredientListItem(IngredientListItemDAO *item, QObject *parent)
	: QObject(parent),
	  m_item(item),
	  m_mult(1)
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

qint32 IngredientListItem::quantity() const
{
	qint32 f = m_item->quantity();
	if (f == 0) return 1;
	return f;
}

void IngredientListItem::setQuantity(qint32 f)
{
	if (f != quantity()) {
		m_item->setQuantity(f);
		if (m_item->save()) {
			notifyValuesChanged();
		}
	}
}

qint32 IngredientListItem::calcQuantity() const
{
	return quantity() * multiplicator();
}

void IngredientListItem::updateQuantity(qint32 q)
{
	setQuantity(q / multiplicator());
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
	return fat() * calcQuantity();
}

void IngredientListItem::updateFat(qreal f)
{
	setFat(f / calcQuantity());
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
	return protein() * calcQuantity();
}

void IngredientListItem::updateProtein(qreal p)
{
	setProtein(p / calcQuantity());
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
	return carbs() * calcQuantity();
}

void IngredientListItem::updateCarbs(qreal c)
{
	setCarbs(c / calcQuantity());
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
	return calories() * calcQuantity();
}

void IngredientListItem::updateCalories(qreal c)
{
	setCalories(c / calcQuantity());
}

qint32 IngredientListItem::multiplicator() const
{
	return m_mult;
}

void IngredientListItem::setMultiplicator(qint32 m)
{
	if (m != m_mult) {
		if (m != 0)
			m_mult = m;
		emit multiplicatorChanged();
		notifyValuesChanged();
	}
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
	emit quantityChanged();
	emit fatChanged();
	emit proteinChanged();
	emit carbsChanged();
	emit caloriesChanged();
}
