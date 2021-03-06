#include "ingredientitemlist.h"
#include "dao/dao.h"
#include "dao/ingredientdao.h"
#include "dao/mealdao.h"
#include "ingredientlist.h"
#include <QTextStream>

IngredientItemList::IngredientItemList(QObject *parent)
	: QObject(parent),
	  m_id(0),
	  m_mult(1)
{

}

IngredientItemList::~IngredientItemList()
{
}

IngredientItemList *IngredientItemList::loadList(QObject *parent, DAOFacade *facade, qint32 id)
{
	IngredientItemList *ret = new IngredientItemList(parent);
	ret->m_facade = facade;
	ret->m_id = id;

	QList<IngredientListItemDAO *> items = facade->loadIngredientListItems(id);
	for (auto i : items) {
		IngredientListItem *l = new IngredientListItem(i, ret);
		ret->connectSignals(l);
		ret->m_data << l;
	}

	return ret;
}

void IngredientItemList::copyInto(IngredientItemList *other, bool save)
{
	Q_ASSERT(this != other);

	for (auto i : m_data) {
		other->m_data.append(i->copyInto(other->id(), save));
	}
}

bool IngredientItemList::appendFromImport(QList<ImportExportHelper::Item> items)
{
	for (auto i : items) {
		auto item = m_facade->createIngredientListItem(m_id);
		item->setName(i.name);
		auto ili = new IngredientListItem(item, this);

		tryConnectItemToIngredientByName(ili, UpdateField::None);

		item->setQuantity(i.quantity);
		item->setFat(i.fat);
		item->setCarbs(i.carbs);
		item->setProtein(i.protein);
		item->setCalories(i.calories);

		m_data.append(ili);
		item->save();
	}

	return true;
}

QList<ImportExportHelper::Item> IngredientItemList::toExportData() const
{
	QList<ImportExportHelper::Item> itms;
	for (IngredientListItem *i : m_data) {
		ImportExportHelper::Item itm;
		itm.name = i->name();
		itm.quantity = i->quantity();
		itm.fat = i->fat();
		itm.carbs = i->carbs();
		itm.protein = i->protein();
		itm.calories = i->calories();
		itms << itm;
	}
	return itms;
}

qint32 IngredientItemList::id() const
{
	return m_id;
}

QQmlListProperty<IngredientListItem> IngredientItemList::items()
{
	return QQmlListProperty<IngredientListItem> (this, nullptr, &IngredientItemList::countFunc, &IngredientItemList::atFunc);
}

QList<IngredientListItem *> IngredientItemList::ingredients()
{
	return m_data;
}

void IngredientItemList::createItem(const QString &name)
{
	IngredientListItemDAO *it = m_facade->createIngredientListItem(m_id);
	it->setName(name);
	it->setQuantity(100);

	if (it->save()) {
		IngredientListItem *id = new IngredientListItem(it, this);
		m_data.append(id);
		id->setMultiplicator(m_mult);
		connectSignals(id);
		emit itemsChanged();
		notifySumsChanged();
	} else {
		delete it;
	}
}

void IngredientItemList::createItemForIngredient(qint32 ingredientId)
{
	if (ingredientId < 0) {
		return;
	}

	QScopedPointer<IngredientListItemDAO> m(m_facade->createIngredientListItem(m_id));
	if (!m) {
		return;
	}

	QScopedPointer<IngredientDAO> r(m_facade->loadIngredient(ingredientId));
	if (!r || r->state() == DAOBase::State::New) {
		return;
	}

	updateItemFromIngredient(m.data(), r.data());

	if (m->save()) {
		IngredientListItem *md = new IngredientListItem(m.take(), this);
		m_data.append(md);
		md->setMultiplicator(m_mult);
		connectSignals(md);
		emit itemsChanged();
		notifySumsChanged();
	}
}

bool IngredientItemList::createIngredientFromItem(qint32 idx)
{
	if (idx < 0 || idx >= m_data.count()) {
		return false;
	}

	IngredientListItem *m = m_data[idx];
	if (m->isConnectedToIngredient()) {
		return false;
	}

	QScopedPointer<IngredientDAO> r(m_facade->createIngredient(m->name()));
	if (!r || r->state() != DAOBase::State::New) {
		if (tryConnectItemToIngredientByName(m)) {
			m->m_item->save();
			m->notifyValuesChanged();
		}
		return false;
	}

	r->setDefaultQuantity((m->quantity() == 0) ? 1 : m->quantity());
	r->setReferenceQuantity(100);
	qreal f = qreal(r->defaultQuantity()) / r->referenceQuantity();
	r->setFat(m->calcFat()/f);
	r->setProtein(m->calcProtein()/f);
	r->setCarbs(m->calcCarbs()/f);
	r->setCalories(m->calcCalories()/f);

	if (r->save()) {
		m->setIngredientId(r->id());
		IngredientNotifier::instance()->notifyChanges();
		return true;
	}

	return false;
}

void IngredientItemList::createItemFromMeal(const MealDAO *meal)
{
	if (!meal) return;

	QScopedPointer<IngredientListItemDAO> m(m_facade->createIngredientListItem(m_id));
	if (!m) {
		return;
	}

	updateItemFromMeal(m.data(), meal);

	if (m->save()) {
		IngredientListItem *md = new IngredientListItem(m.take(), this);
		m_data.append(md);
		md->setMultiplicator(m_mult);
		connectSignals(md);
		emit itemsChanged();
		notifySumsChanged();
	}
}

void IngredientItemList::removeItem(qint32 idx)
{
	if (idx < 0 || idx >= m_data.count()) {
		return;
	}

	auto m = m_data.takeAt(idx);
	m->erase();
	m->deleteLater();
	m->disconnect();
	emit itemsChanged();
	notifySumsChanged();
}

void IngredientItemList::clear()
{
	for (auto i : m_data) {
		i->deleteLater();
		i->disconnect();
		i->erase();
	}

	emit itemsChanged();
	notifySumsChanged();
}

qreal IngredientItemList::sumFat() const
{
	qreal sum = 0;
	for (auto m : m_data) {
		sum += m->calcFat();
	}
	return sum;
}

qreal IngredientItemList::sumProtein() const
{
	qreal sum = 0;
	for (auto m : m_data) {
		sum += m->calcProtein();
	}
	return sum;
}

qreal IngredientItemList::sumCarbs() const
{
	qreal sum = 0;
	for (auto m : m_data) {
		sum += m->calcCarbs();
	}
	return sum;
}

qreal IngredientItemList::sumCalories() const
{
	qreal sum = 0;
	for (auto m : m_data) {
		sum += m->calcCalories();
	}
	return sum;
}

qreal IngredientItemList::multiplicator() const
{
	return m_mult;
}

bool IngredientItemList::isEmpty() const
{
	return m_data.isEmpty();
}

void IngredientItemList::setMultiplicator(qreal m)
{
	if (m != m_mult) {
		m_mult = m;
		for (auto i : m_data) {
			i->disconnect();
			i->setMultiplicator(m);
			connectSignals(i);
		}
		emit multiplicatorChanged();
		notifySumsChanged();
	}
}

IngredientListItem *IngredientItemList::atFunc(QQmlListProperty<IngredientListItem> *p, int i)
{
	return static_cast<IngredientItemList *> (p->object)->m_data.at(i);
}

int IngredientItemList::countFunc(QQmlListProperty<IngredientListItem> *p)
{
	return static_cast<IngredientItemList *> (p->object)->m_data.count();
}

void IngredientItemList::connectSignals(IngredientListItem *m)
{
	connect(m, &IngredientListItem::fatChanged, this, &IngredientItemList::sumFatChanged);
	connect(m, &IngredientListItem::proteinChanged, this, &IngredientItemList::sumProteinChanged);
	connect(m, &IngredientListItem::carbsChanged, this, &IngredientItemList::sumCarbsChanged);
	connect(m, &IngredientListItem::caloriesChanged, this, &IngredientItemList::sumCaloriesChanged);
	//connect(m, &IngredientListItem::quantityChanged, this, &IngredientItemList::notifySumsChanged);
	connect(m, &IngredientListItem::multiplicatorChanged, this, &IngredientItemList::notifySumsChanged);
}

void IngredientItemList::notifySumsChanged()
{
	emit sumFatChanged();
	emit sumProteinChanged();
	emit sumCarbsChanged();
	emit sumCaloriesChanged();
}

void IngredientItemList::updateItemFromIngredient(IngredientListItemDAO *il, IngredientDAO *i, UpdateFields fields)
{
	if (fields.testFlag(UpdateField::Name)) il->setName(i->name());
	if (fields.testFlag(UpdateField::Quantity)) il->setQuantity(i->defaultQuantity());
	if (fields.testFlag(UpdateField::Id)) il->setIngredientId(i->id());
	if (fields.testFlag(UpdateField::Values)) {
		qint32 f = i->referenceQuantity() == 0 ? 1 : i->referenceQuantity();
		il->setFat(i->fat() / f);
		il->setProtein(i->protein() / f);
		il->setCarbs(i->carbs() / f);
		il->setCalories(i->calories() / f);
	}
}

void IngredientItemList::updateItemFromMeal(IngredientListItemDAO *il, const MealDAO *m, UpdateFields fields)
{
	if (fields.testFlag(UpdateField::Name)) il->setName(m->name());
	if (fields.testFlag(UpdateField::Quantity)) il->setQuantity(m->quantity());
	if (fields.testFlag(UpdateField::Id)) il->setIngredientId(m->ingredientId());
	if (fields.testFlag(UpdateField::Values)) {
		// These values are already scaled to 1, no need for quantity factor
		il->setFat(m->fat());
		il->setProtein(m->protein());
		il->setCarbs(m->carbs());
		il->setCalories(m->calories());
	}
}

bool IngredientItemList::tryConnectItemToIngredientByName(IngredientListItem *i, UpdateFields fields)
{
	QScopedPointer<IngredientDAO> r(m_facade->loadIngredientByName(i->name()));
	if (r.data()) {
		i->setIngredientId(r->id());
		updateItemFromIngredient(i->m_item, r.data(), fields);
		return true;
	}
	return false;
}
