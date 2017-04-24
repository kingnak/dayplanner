#ifndef INGREDIENTLIST_H
#define INGREDIENTLIST_H

#include <QAbstractListModel>
#include <QList>
#include <QHash>

class DAOFacade;
class IngredientDAO;
class IngredientStatsDAO;
class IngredientStats;
class IngredientNotifier;

class IngredientList : public QAbstractListModel
{
	Q_OBJECT

	Q_PROPERTY(QObject* stats READ stats NOTIFY statsChanged)
public:
    IngredientList();
    ~IngredientList();

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

	Q_INVOKABLE QObject *loadDataForIngredient(qint32 id);
	Q_INVOKABLE void clearIngredientCache();
	Q_INVOKABLE void removeIngredient(qint32 id);
	QObject *stats();

signals:
	void statsChanged();

private:
    void load();

private:
    QList<IngredientDAO*> m_data;
	QMap<qint32, QObject*> m_ingredientCache;
	IngredientStats *m_stats;
};

class IngredientNotifier : public QObject
{
	Q_OBJECT

private:
	IngredientNotifier() : QObject(nullptr) {}

public:
	static IngredientNotifier *instance() {
		static IngredientNotifier inst_;
		return &inst_;
	}

public slots:
	void notifyChanges() {
		emit ingredientsChanged();
	}

signals:
	void ingredientsChanged();
};

class IngredientStats : public QObject
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
	IngredientStats(DAOFacade *facade, QObject *parent = nullptr)
		: QObject(parent),
		  m_stats(nullptr),
		  m_facade(facade)
	{
		connect(IngredientNotifier::instance(), &IngredientNotifier::ingredientsChanged, this, &IngredientStats::updateStats);
		updateStats();
	}

	~IngredientStats();

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
	IngredientStatsDAO *m_stats;
	DAOFacade *m_facade;
};

#endif // INGREDIENTLIST_H
