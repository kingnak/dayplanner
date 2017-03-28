#ifndef RECIPELIST_H
#define RECIPELIST_H

#include <QAbstractListModel>
#include <QList>
#include <QVariantMap>

class RecipeList : public QAbstractListModel
{
public:
    RecipeList();

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;

    QHash<int, QByteArray> roleNames() const;
    enum {
        NameRole = Qt::UserRole + 1,
        FatRole,
        ProteinRole,
        CarbsRole,
        CaloriesRole,
        QuantityRole,
        UrlRole
    };

private:
    void load();

private:
    QList<QVariantMap> m_data;
};

#endif // RECIPELIST_H
