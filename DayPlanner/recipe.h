#ifndef RECIPE_H
#define RECIPE_H

#include <QObject>
#include "dao/recipedao.h"
#include "ingredientitemlist.h"

class RecipeLoader;

class Recipe : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QObject* items READ items NOTIFY itemsChanged)
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(qint32 servings READ servings WRITE setServings NOTIFY servingsChanged)
	Q_PROPERTY(qint32 defaultServings READ defaultServings WRITE setDefaultServings NOTIFY defaultServingsChanged)
	Q_PROPERTY(qreal fat READ fat WRITE setFat NOTIFY fatChanged)
	Q_PROPERTY(qreal protein READ protein WRITE setProtein NOTIFY proteinChanged)
	Q_PROPERTY(qreal carbs READ carbs WRITE setCarbs NOTIFY carbsChanged)
	Q_PROPERTY(qreal calories READ calories WRITE setCalories NOTIFY caloriesChanged)
	Q_PROPERTY(qint32 displayServings READ multiplicator WRITE setMultiplicator NOTIFY multiplicatorChanged)

public:
	explicit Recipe(QObject *parent = 0);
	explicit Recipe(RecipeDAO *recipe, QObject *parent = 0);
	~Recipe();

	static Recipe *loadRecipeById(qint32 id);

	qint32 id() const;

	IngredientItemList *items() const;
	QString name() const;
	qint32 servings() const;
	qint32 defaultServings() const;
	qreal fat() const;
	qreal protein() const;
	qreal carbs() const;
	qreal calories() const;
	qint32 multiplicator() const;

	void setName(const QString &n);
	void setServings(qint32 s);
	void setDefaultServings(qint32 ds);
	void setFat(qreal f);
	void setProtein(qreal p);
	void setCarbs(qreal c);
	void setCalories(qreal c);
	void setMultiplicator(qint32 m);

public slots:
	void updateFat();
	void updateProtein();
	void updateCarbs();
	void updateCalories();

signals:
	void itemsChanged();
	void nameChanged();
	void servingsChanged();
	void defaultServingsChanged();
	void fatChanged();
	void proteinChanged();
	void carbsChanged();
	void caloriesChanged();
	void multiplicatorChanged();

private:
	void updateItemSums();

private:
	RecipeDAO *m_recipe;
	IngredientItemList *m_items;
};

class RecipeLoader : public QObject
{
	Q_OBJECT
	RecipeLoader(QObject *parent = 0) : QObject(parent) {}
public:
	static RecipeLoader *instance();
	Q_INVOKABLE Recipe *loadRecipeById(qint32 id);
	void removeRecipe(Recipe *r);

private:
	QHash<qint32, Recipe *> m_cache;

};

#endif // RECIPE_H
