#include "recipelist.h"
#include <QtSql>
#include "dao/dao.h"
#include "dao/recipedao.h"
#include "dao/recipestatsdao.h"
#include "recipe.h"

RecipeList::RecipeList()
	: m_stats(nullptr)
{
	connect(RecipeNotifier::instance(), &RecipeNotifier::recipesChanged, [this]() { this->load(); });
    load();
}

RecipeList::~RecipeList()
{
    qDeleteAll(m_data);
}

QVariant RecipeList::data(const QModelIndex &index, int role) const
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
    case QuantityRole:
        return m_data[index.row()]->quantity();
    case UrlRole:
        return m_data[index.row()]->url();
    default:
        return QVariant();
    }
}

int RecipeList::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_data.count();
}

QHash<int, QByteArray> RecipeList::roleNames() const
{
    QHash<int, QByteArray> ret;
    ret[IdRole] = "itemId";
    ret[NameRole] = "name";
    ret[FatRole] = "fat";
    ret[ProteinRole] = "protein";
    ret[CarbsRole] = "carbs";
    ret[CaloriesRole] = "calories";
    ret[QuantityRole] = "quantity";
    ret[UrlRole] = "url";
	return ret;
}

QObject *RecipeList::loadDataForRecipe(qint32 id)
{
	if (!m_recipeCache.contains(id)) {
		Recipe *r =new Recipe(globalDAOFacade()->loadRecipe(id), this);
		m_recipeCache[id] = r;
	}
	return m_recipeCache[id];
}

void RecipeList::clearRecipeCache()
{
	for (QObject *o : m_recipeCache.values()) {
		o->deleteLater();
	}
	m_recipeCache.clear();
}

QObject *RecipeList::stats()
{
	if (!m_stats) {
		m_stats = new RecipeStats(globalDAOFacade(), this);
	}
	return m_stats;
}

void RecipeList::load()
{
    beginResetModel();
    QList<RecipeDAO*> oldList = m_data;
    m_data.clear();
    m_data = globalDAOFacade()->loadRecipes();
    endResetModel();

    qDeleteAll(oldList);
}

/////////////////////////////////////////////

RecipeStats::~RecipeStats()
{
	delete m_stats;
}

qreal RecipeStats::maxFat() const
{
	return m_stats->maxFat();
}

qreal RecipeStats::minFat() const
{
	return m_stats->minFat();
}

qreal RecipeStats::maxProtein() const
{
	return m_stats->maxProtein();
}

qreal RecipeStats::minProtein() const
{
	return m_stats->minProtein();
}

qreal RecipeStats::maxCarbs() const
{
	return m_stats->maxCarbs();
}

qreal RecipeStats::minCarbs() const
{
	return m_stats->minCarbs();
}

qreal RecipeStats::maxCalories() const
{
	return m_stats->maxCalories();
}

qreal RecipeStats::minCalories() const
{
	return m_stats->minCalories();
}

void RecipeStats::updateStats()
{
	delete m_stats;
	m_stats = m_facade->loadRecipeStats();
	emit statsChanged();
}
