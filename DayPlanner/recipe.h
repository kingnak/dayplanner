#ifndef RECIPE_H
#define RECIPE_H

#include <QObject>
#include "dao/recipedao.h"

class Meal;

class Recipe : public QObject
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
	explicit Recipe(QObject *parent = 0);
	explicit Recipe(RecipeDAO *recipe, QObject *parent = 0);
	~Recipe();

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
	RecipeDAO *m_recipe;
};

#endif // RECIPE_H
