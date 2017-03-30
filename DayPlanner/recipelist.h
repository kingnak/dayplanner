#ifndef RECIPELIST_H
#define RECIPELIST_H

#include <QAbstractListModel>
#include <QList>
#include <QVariantMap>

class RecipeDAO;

class RecipeList : public QAbstractListModel
{
public:
    RecipeList();
    ~RecipeList();

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;

    QHash<int, QByteArray> roleNames() const;
    enum {
        IdRole = Qt::UserRole + 1,
        NameRole,
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
    QList<RecipeDAO*> m_data;
};

#endif // RECIPELIST_H
