#ifndef RECIPE_H
#define RECIPE_H

#include <QObject>
#include "dao/recipedao.h"
#include "dao/recipetemplatedao.h"
#include "ingredientitemlist.h"

class RecipeLoader;
class Meal;

class RecipeDAOWrapper;

class Recipe : public QObject
{
	Q_OBJECT

	Q_PROPERTY(bool isTemplate READ isTemplate NOTIFY isTemplateChanged)
	Q_PROPERTY(QObject* items READ items NOTIFY itemsChanged)
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(qint32 servings READ servings WRITE setServings NOTIFY servingsChanged)
	Q_PROPERTY(qint32 defaultServings READ defaultServings WRITE setDefaultServings NOTIFY defaultServingsChanged)
	Q_PROPERTY(qreal fat READ fat WRITE setFat NOTIFY fatChanged)
	Q_PROPERTY(qreal protein READ protein WRITE setProtein NOTIFY proteinChanged)
	Q_PROPERTY(qreal carbs READ carbs WRITE setCarbs NOTIFY carbsChanged)
	Q_PROPERTY(qreal calories READ calories WRITE setCalories NOTIFY caloriesChanged)
	Q_PROPERTY(qint32 displayServings READ displayServings WRITE setDisplayServings NOTIFY displayServingsChanged)
	Q_PROPERTY(bool nutritionValuesOverridden READ nutritionValuesOverridden WRITE setNutritionValuesOverridden NOTIFY nutritionValuesOverriddenChanged)
	Q_PROPERTY(Meal* writeBackMeal READ writeBackMeal WRITE setWriteBackMeal NOTIFY writeBackMealChanged)

public:
	explicit Recipe(QObject *parent = 0);
	explicit Recipe(RecipeDAO *recipe, QObject *parent = 0);
	explicit Recipe(RecipeTemplateDAO *recipe, QObject *parent = 0);
	~Recipe();

	static Recipe *loadRecipeById(qint32 id);

	Q_INVOKABLE void adjustForServings(qint32 servings);
	Q_INVOKABLE void deleteLater() { QObject::deleteLater(); }

	qint32 id() const;

	bool isTemplate() const;
	IngredientItemList *items() const;
	QString name() const;
	qint32 servings() const;
	qint32 defaultServings() const;
	qint32 displayServings() const;
	qreal fat() const;
	qreal protein() const;
	qreal carbs() const;
	qreal calories() const;
	bool nutritionValuesOverridden() const;
	Meal *writeBackMeal() const;

	qreal multiplicator() const;

	void setName(const QString &n);
	void setServings(qint32 s);
	void setDefaultServings(qint32 ds);
	void setDisplayServings(qint32 ds);
	void setFat(qreal f);
	void setFat(qreal f, bool force);
	Q_INVOKABLE void overrideFat(qreal f);
	void setProtein(qreal p);
	void setProtein(qreal p, bool force);
	Q_INVOKABLE void overrideProtein(qreal p);
	void setCarbs(qreal c);
	void setCarbs(qreal c, bool force);
	Q_INVOKABLE void overrideCarbs(qreal c);
	void setCalories(qreal c);
	void setCalories(qreal c, bool force);
	Q_INVOKABLE void overrideCalories(qreal c);
	void setNutritionValuesOverridden(bool o);
	void setWriteBackMeal(Meal *m);

public slots:
	void updateFatFromSum();
	void updateProteinFromSum();
	void updateCarbsFromSum();
	void updateCaloriesFromSum();

signals:
	void isTemplateChanged();
	void itemsChanged();
	void nameChanged();
	void servingsChanged();
	void defaultServingsChanged();
	void displayServingsChanged();
	void fatChanged();
	void proteinChanged();
	void carbsChanged();
	void caloriesChanged();
	void multiplicatorChanged();
	void writeBackMealChanged();
	void nutritionValuesOverriddenChanged();

private:
	void updateItemSums();
	void updateItemMultiplicators();
	void init();

private:
	RecipeDAOWrapper *m_recipe;
	IngredientItemList *m_items;
	Meal *m_writeBack;
	qint32 m_dispServings;
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
