#ifndef INGREDIENTITEMLIST_H
#define INGREDIENTITEMLIST_H

#include <QObject>
#include <QQmlListProperty>
#include "ingredientlistitem.h"

class DAOFacade;
class IngredientDAO;

class IngredientItemList : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QQmlListProperty<IngredientListItem> items READ items NOTIFY itemsChanged)
	Q_PROPERTY(qreal sumFat READ sumFat NOTIFY sumFatChanged)
	Q_PROPERTY(qreal sumProtein READ sumProtein NOTIFY sumProteinChanged)
	Q_PROPERTY(qreal sumCarbs READ sumCarbs NOTIFY sumCarbsChanged)
	Q_PROPERTY(qreal sumCalories READ sumCalories NOTIFY sumCaloriesChanged)
	Q_PROPERTY(qint32 multiplicator READ multiplicator WRITE setMultiplicator NOTIFY multiplicatorChanged)
	Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY itemsChanged)

public:
	explicit IngredientItemList(QObject *parent = 0);
	~IngredientItemList();

	static IngredientItemList *loadList(QObject *parent, DAOFacade *facade, qint32 id);

	QQmlListProperty<IngredientListItem> items();

	Q_INVOKABLE void createItem(const QString &name);
	Q_INVOKABLE void createItemForIngredient(qint32 ingredientId);
	Q_INVOKABLE void removeItem(qint32 idx);

	qreal sumFat() const;
	qreal sumProtein() const;
	qreal sumCarbs() const;
	qreal sumCalories() const;
	qint32 multiplicator() const;

	bool isEmpty() const;

	void setMultiplicator(qint32 m);

signals:
	void itemsChanged();
	void sumFatChanged();
	void sumProteinChanged();
	void sumCarbsChanged();
	void sumCaloriesChanged();
	void multiplicatorChanged();

private:
	static IngredientListItem *atFunc(QQmlListProperty<IngredientListItem> *p, int i);
	static int countFunc(QQmlListProperty<IngredientListItem> *p);
	void connectSignals(IngredientListItem *m);
	void notifySumsChanged();

	enum UpdateField {
		Name = 0x01,
		Id = 0x02,
		Quantity = 0x04,
		Values = 0x08,
		All = 0x0F
	};
	Q_DECLARE_FLAGS(UpdateFields, UpdateField)

	void updateItemFromIngredient(IngredientListItemDAO *il, IngredientDAO *i, UpdateFields fields = UpdateField::All);
	bool tryConnectItemToIngredientByName(IngredientListItem *i, UpdateFields fields = UpdateField::All);

private:
	qint32 m_id;
	QList<IngredientListItem *> m_data;
	DAOFacade *m_facade;
	qint32 m_mult;
};

#endif // INGREDIENTITEMLIST_H
