#ifndef RECIPELIST_H
#define RECIPELIST_H

#include <QAbstractListModel>
#include <QList>
#include <QHash>

class DAOFacade;
class RecipeDAO;
class RecipeStatsDAO;
class RecipeStats;
class RecipeNotifier;

class RecipeList : public QAbstractListModel
{
	Q_OBJECT
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

	Q_INVOKABLE QObject *loadDataForRecipe(qint32 id);
	Q_INVOKABLE void clearRecipeCache();
	Q_INVOKABLE QObject *stats();

private:
    void load();

private:
    QList<RecipeDAO*> m_data;
	QMap<qint32, QObject*> m_recipeCache;
	RecipeStats *m_stats;
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

class RecipeStats : public QObject
{
	Q_OBJECT

	Q_PROPERTY(qreal maxFat READ maxFat NOTIFY statsChanged)
	Q_PROPERTY(qreal minFat READ minFat NOTIFY statsChanged)
	Q_PROPERTY(qreal maxProtein READ maxProtein NOTIFY statsChanged)
	Q_PROPERTY(qreal minProtein READ minProtein NOTIFY statsChanged)
	Q_PROPERTY(qreal maxCarbs READ maxCarbs NOTIFY statsChanged)
	Q_PROPERTY(qreal minCarbs READ minCarbs NOTIFY statsChanged)
	Q_PROPERTY(qreal maxCalories READ maxCalories NOTIFY statsChanged)
	Q_PROPERTY(qreal minCalories READ minCalories NOTIFY statsChanged)

public:
	RecipeStats(DAOFacade *facade, QObject *parent = nullptr)
		: QObject(parent),
		  m_stats(nullptr),
		  m_facade(facade)
	{
		connect(RecipeNotifier::instance(), &RecipeNotifier::recipesChanged, this, &RecipeStats::updateStats);
		updateStats();
	}

	~RecipeStats();

	qreal maxFat() const;
	qreal minFat() const;
	qreal maxProtein() const;
	qreal minProtein() const;
	qreal maxCarbs() const;
	qreal minCarbs() const;
	qreal maxCalories() const;
	qreal minCalories() const;

signals:
	void statsChanged();

private slots:
	void updateStats();

private:
	RecipeStatsDAO *m_stats;
	DAOFacade *m_facade;
};

#endif // RECIPELIST_H
