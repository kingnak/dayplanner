#ifndef INGREDIENTLISTITEM_H
#define INGREDIENTLISTITEM_H

#include <QObject>
#include "dao/ingredientlistitemdao.h"

class IngredientListItem : public QObject
{
	Q_OBJECT

	Q_PROPERTY(qint32 ingredientId READ ingredientId WRITE setIngredientId NOTIFY ingredientIdChanged)
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(qint32 quantity READ calcQuantity WRITE updateQuantity NOTIFY quantityChanged)
	Q_PROPERTY(qint32 baseQuantity READ quantity WRITE setQuantity NOTIFY quantityChanged)
	Q_PROPERTY(qreal calcFat READ calcFat WRITE updateFat NOTIFY fatChanged)
	Q_PROPERTY(qreal fat READ fat WRITE setFat NOTIFY fatChanged)
	Q_PROPERTY(qreal calcProtein READ calcProtein WRITE updateProtein NOTIFY proteinChanged)
	Q_PROPERTY(qreal protein READ protein WRITE setProtein NOTIFY proteinChanged)
	Q_PROPERTY(qreal calcCarbs READ calcCarbs WRITE updateCarbs NOTIFY carbsChanged)
	Q_PROPERTY(qreal carbs READ carbs WRITE setCarbs NOTIFY carbsChanged)
	Q_PROPERTY(qreal calcCalories READ calcCalories WRITE updateCalories NOTIFY caloriesChanged)
	Q_PROPERTY(qreal calories READ calories WRITE setCalories NOTIFY caloriesChanged)
	Q_PROPERTY(qreal multiplicator READ multiplicator WRITE setMultiplicator NOTIFY multiplicatorChanged)
	Q_PROPERTY(bool isConnectedToIngredient READ isConnectedToIngredient NOTIFY ingredientIdChanged)

public:
	explicit IngredientListItem(QObject *parent = 0);
	explicit IngredientListItem(IngredientListItemDAO *item, QObject *parent = 0);
	~IngredientListItem();

	bool erase();

	QString name() const;
	void setName(const QString &n);

	qint32 quantity() const;
	void setQuantity(qint32 q);
	qint32 calcQuantity() const;
	void updateQuantity(qint32 q);

	qreal fat() const;
	void setFat(qreal f);
	qreal calcFat() const;
	void updateFat(qreal f);

	qreal protein() const;
	void setProtein(qreal p);
	qreal calcProtein() const;
	void updateProtein(qreal p);

	qreal carbs() const;
	void setCarbs(qreal c);
	qreal calcCarbs() const;
	void updateCarbs(qreal c);

	qreal calories() const;
	void setCalories(qreal c);
	qreal calcCalories() const;
	void updateCalories(qreal c);

	qreal multiplicator() const;
	void setMultiplicator(qreal m);

	qint32 ingredientId() const;
	void setIngredientId(qint32 id);
	bool isConnectedToIngredient() const;

signals:
	void nameChanged();
	void quantityChanged();
	void fatChanged();
	void proteinChanged();
	void carbsChanged();
	void caloriesChanged();
	void multiplicatorChanged();
	void ingredientIdChanged();

private:
	void notifyValuesChanged();

private:
	IngredientListItemDAO *m_item;
	qreal m_mult;

	friend class IngredientItemList;
};

#endif // INGREDIENTLISTITEM_H
