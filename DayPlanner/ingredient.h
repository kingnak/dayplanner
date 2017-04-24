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
	Q_PROPERTY(qint32 quantity READ quantity WRITE setQuantity NOTIFY quantityChanged)
	Q_PROPERTY(qreal fat READ fat WRITE setFat NOTIFY fatChanged)
	Q_PROPERTY(qreal protein READ protein WRITE setProtein NOTIFY proteinChanged)
	Q_PROPERTY(qreal carbs READ carbs WRITE setCarbs NOTIFY carbsChanged)
	Q_PROPERTY(qreal calories READ calories WRITE setCalories NOTIFY caloriesChanged)
	Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)

public:
	explicit Ingredient(QObject *parent = 0);
	explicit Ingredient(IngredientDAO *ingredient, QObject *parent = 0);
	~Ingredient();

	qint32 id() const;

	QString name() const;
	void setName(const QString &n);

	qint32 quantity() const;
	void setQuantity(qint32 q);

	qreal fat() const;
	void setFat(qreal f);

	qreal protein() const;
	void setProtein(qreal p);

	qreal carbs() const;
	void setCarbs(qreal c);

	qreal calories() const;
	void setCalories(qreal c);

	QString url() const;
	void setUrl(const QString &u);

	Q_INVOKABLE bool save();
	Q_INVOKABLE bool reset();
	Q_INVOKABLE void calcTo100();

signals:
	void notNotified();
	void nameChanged();
	void quantityChanged();
	void fatChanged();
	void proteinChanged();
	void carbsChanged();
	void caloriesChanged();
	void urlChanged();

private:
	IngredientDAO *m_ingredient;
};

#endif // INGREDIENT_H
