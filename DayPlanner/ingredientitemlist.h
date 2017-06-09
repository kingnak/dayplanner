#ifndef INGREDIENTITEMLIST_H
#define INGREDIENTITEMLIST_H

#include <QObject>
#include <QQmlListProperty>
#include "ingredientlistitem.h"

class DAOFacade;
class IngredientDAO;
class MealDAO;

class QTextStream;

class IngredientItemList : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QQmlListProperty<IngredientListItem> items READ items NOTIFY itemsChanged)
	Q_PROPERTY(qreal sumFat READ sumFat NOTIFY sumFatChanged)
	Q_PROPERTY(qreal sumProtein READ sumProtein NOTIFY sumProteinChanged)
	Q_PROPERTY(qreal sumCarbs READ sumCarbs NOTIFY sumCarbsChanged)
	Q_PROPERTY(qreal sumCalories READ sumCalories NOTIFY sumCaloriesChanged)
	Q_PROPERTY(qreal multiplicator READ multiplicator WRITE setMultiplicator NOTIFY multiplicatorChanged)
	Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY itemsChanged)

public:
	explicit IngredientItemList(QObject *parent = 0);
	~IngredientItemList();

	static IngredientItemList *loadList(QObject *parent, DAOFacade *facade, qint32 id);
	void copyInto(IngredientItemList *other, bool save);

	QString toText() const;
	void toText(QTextStream &ts) const;

	bool fromText(const QString &text);

	qint32 id() const;
	QQmlListProperty<IngredientListItem> items();

	QList<IngredientListItem *> ingredients();

	Q_INVOKABLE void createItem(const QString &name);
	Q_INVOKABLE void createItemForIngredient(qint32 ingredientId);
	Q_INVOKABLE bool createIngredientFromItem(qint32 idx);
	void createItemFromMeal(const MealDAO *meal);
	Q_INVOKABLE void removeItem(qint32 idx);

	qreal sumFat() const;
	qreal sumProtein() const;
	qreal sumCarbs() const;
	qreal sumCalories() const;
	qreal multiplicator() const;

	bool isEmpty() const;

	void setMultiplicator(qreal m);

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
		None = 0x00,
		Name = 0x01,
		Id = 0x02,
		Quantity = 0x04,
		Values = 0x08,
		All = 0x0F
	};
	Q_DECLARE_FLAGS(UpdateFields, UpdateField)

	void updateItemFromIngredient(IngredientListItemDAO *il, IngredientDAO *i, UpdateFields fields = UpdateField::All);
	void updateItemFromMeal(IngredientListItemDAO *il, const MealDAO *m, UpdateFields fields = UpdateField::All);
	bool tryConnectItemToIngredientByName(IngredientListItem *i, UpdateFields fields = UpdateField::All);

private:
	qint32 m_id;
	QList<IngredientListItem *> m_data;
	DAOFacade *m_facade;
	qreal m_mult;
};

#endif // INGREDIENTITEMLIST_H
