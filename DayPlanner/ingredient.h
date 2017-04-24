#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QObject>
#include "dao/ingredientdao.h"

class Meal;

class Ingredient : public QObject
{
	Q_OBJECT

	Q_PROPERTY(qint32 id READ id NOTIFY notNotified)
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(qint32 referenceQuantity READ referenceQuantity WRITE setReferenceQuantity NOTIFY referenceQuantityChanged)
	Q_PROPERTY(qint32 defaultQuantity READ defaultQuantity WRITE setDefaultQuantity NOTIFY defaultQuantityChanged)
	Q_PROPERTY(qreal fat READ fat WRITE setFat NOTIFY fatChanged)
	Q_PROPERTY(qreal protein READ protein WRITE setProtein NOTIFY proteinChanged)
	Q_PROPERTY(qreal carbs READ carbs WRITE setCarbs NOTIFY carbsChanged)
	Q_PROPERTY(qreal calories READ calories WRITE setCalories NOTIFY caloriesChanged)

public:
	explicit Ingredient(QObject *parent = 0);
	explicit Ingredient(IngredientDAO *ingredient, QObject *parent = 0);
	~Ingredient();

	qint32 id() const;

	QString name() const;
	void setName(const QString &n);

	qint32 referenceQuantity() const;
	void setReferenceQuantity(qint32 q);

	qint32 defaultQuantity() const;
	void setDefaultQuantity(qint32 q);

	qreal fat() const;
	void setFat(qreal f);

	qreal protein() const;
	void setProtein(qreal p);

	qreal carbs() const;
	void setCarbs(qreal c);

	qreal calories() const;
	void setCalories(qreal c);

	Q_INVOKABLE bool save();
	Q_INVOKABLE bool reset();
	Q_INVOKABLE void calcTo100();

signals:
	void notNotified();
	void nameChanged();
	void referenceQuantityChanged();
	void defaultQuantityChanged();
	void fatChanged();
	void proteinChanged();
	void carbsChanged();
	void caloriesChanged();

private:
	IngredientDAO *m_ingredient;
};

#endif // INGREDIENT_H
