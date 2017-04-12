#ifndef RECIPELIST_H
#define RECIPELIST_H

#include <QAbstractListModel>
#include <QList>
#include <QHash>

class RecipeDAO;

class RecipeNotifier;

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

class RecipeNotifier : public QObject
{
	Q_OBJECT

private:
	RecipeNotifier() : QObject(nullptr) {}

public:
	static RecipeNotifier *instance() {
		static RecipeNotifier inst_;
		return &inst_;
	}

public slots:
	void notifyChanges() {
		emit recipesChanged();
	}

signals:
	void recipesChanged();
};

#endif // RECIPELIST_H
