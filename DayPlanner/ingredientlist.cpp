#include "ingredientlist.h"
#include <QtSql>
#include "dao/dao.h"
#include "dao/ingredientdao.h"
#include "dao/ingredientstatsdao.h"
#include "ingredient.h"

IngredientList::IngredientList()
	: m_stats(nullptr)
{
	connect(IngredientNotifier::instance(), &IngredientNotifier::ingredientsChanged, [this]() { this->load(); });
    load();
}

IngredientList::~IngredientList()
{
    qDeleteAll(m_data);
}

QVariant IngredientList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return m_data[index.row()]->name();
    case IdRole:
        return m_data[index.row()]->id();
    case FatRole:
        return m_data[index.row()]->fat();
    case ProteinRole:
        return m_data[index.row()]->protein();
    case CarbsRole:
        return m_data[index.row()]->carbs();
    case CaloriesRole:
        return m_data[index.row()]->calories();
	case ReferenceQuantityRole:
		return m_data[index.row()]->referenceQuantity();
	case DefaultQuantityRole:
		return m_data[index.row()]->defaultQuantity();
    default:
        return QVariant();
    }
}

int IngredientList::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_data.count();
}

QHash<int, QByteArray> IngredientList::roleNames() const
{
    QHash<int, QByteArray> ret;
    ret[IdRole] = "itemId";
    ret[NameRole] = "name";
    ret[FatRole] = "fat";
    ret[ProteinRole] = "protein";
    ret[CarbsRole] = "carbs";
    ret[CaloriesRole] = "calories";
	ret[ReferenceQuantityRole] = "quantity";
	ret[DefaultQuantityRole] = "defaultQuantity";
	return ret;
}

QObject *IngredientList::loadDataForIngredient(qint32 id)
{
	if (!m_ingredientCache.contains(id)) {
		Ingredient *r =new Ingredient(globalDAOFacade()->loadIngredient(id), this);
		m_ingredientCache[id] = r;
	}
	return m_ingredientCache[id];
}

void IngredientList::clearIngredientCache()
{
	for (QObject *o : m_ingredientCache.values()) {
		o->deleteLater();
	}
	m_ingredientCache.clear();
}

void IngredientList::removeIngredient(qint32 id)
{
	globalDAOFacade()->removeIngredient(id);
	IngredientNotifier::instance()->notifyChanges();
}

QObject *IngredientList::stats()
{
	if (!m_stats) {
		m_stats = new IngredientStats(globalDAOFacade(), this);
	}
	return m_stats;
}

void IngredientList::load()
{
    beginResetModel();
    QList<IngredientDAO*> oldList = m_data;
    m_data.clear();
    m_data = globalDAOFacade()->loadIngredients();
    endResetModel();

    qDeleteAll(oldList);
}

/////////////////////////////////////////////

IngredientStats::~IngredientStats()
{
	delete m_stats;
}

qreal IngredientStats::maxFat() const
{
	return m_stats->maxFat();
}

qreal IngredientStats::minFat() const
{
	return m_stats->minFat();
}

qreal IngredientStats::maxProtein() const
{
	return m_stats->maxProtein();
}

qreal IngredientStats::minProtein() const
{
	return m_stats->minProtein();
}

qreal IngredientStats::maxCarbs() const
{
	return m_stats->maxCarbs();
}

qreal IngredientStats::minCarbs() const
{
	return m_stats->minCarbs();
}

qreal IngredientStats::maxCalories() const
{
	return m_stats->maxCalories();
}

qreal IngredientStats::minCalories() const
{
	return m_stats->minCalories();
}

void IngredientStats::updateStats()
{
	delete m_stats;
	m_stats = m_facade->loadIngredientStats();
	emit statsChanged();
}
