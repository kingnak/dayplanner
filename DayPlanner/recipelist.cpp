#include "recipelist.h"
#include <QtSql>
#include "dao/db/database.h"

RecipeList::RecipeList()
{
    load();
}

QVariant RecipeList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return m_data[index.row()]["name"];
    case FatRole:
        return m_data[index.row()]["fat"];
    case ProteinRole:
        return m_data[index.row()]["protein"];
    case CarbsRole:
        return m_data[index.row()]["carbs"];
    case CaloriesRole:
        return m_data[index.row()]["calories"];
    case QuantityRole:
        return m_data[index.row()]["quantity"];
    case UrlRole:
        return m_data[index.row()]["url"];
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
    ret[NameRole] = "name";
    ret[FatRole] = "fat";
    ret[ProteinRole] = "protein";
    ret[CarbsRole] = "carbs";
    ret[CaloriesRole] = "calories";
    ret[QuantityRole] = "quantity";
    ret[UrlRole] = "url";
    return ret;
}

// TODO: Make in DbDAO
void RecipeList::load()
{
    beginResetModel();
    m_data.clear();
    QSqlQuery q = DataBase::instance().executeQuery("SELECT * FROM Recipe ORDER BY name ASC");
    while (q.next()) {
        QVariantMap m;
        for (int i = 0; i < q.record().count(); ++i) {
            m[q.record().fieldName(i)] = q.record().value(i);
        }
        m_data << m;
    }
    endResetModel();
}
