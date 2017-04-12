#include "recipelist.h"
#include <QtSql>
#include "dao/dao.h"
#include "dao/recipedao.h"


RecipeList::RecipeList()
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

void RecipeList::load()
{
    beginResetModel();
    QList<RecipeDAO*> oldList = m_data;
    m_data.clear();
    m_data = globalDAOFacade()->loadRecipes();
    endResetModel();

    qDeleteAll(oldList);
}
