
#ifndef MEALLIST_H
#define MEALLIST_H

#include <QObject>
#include <QDate>
#include <QQmlListProperty>
#include "meal.h"

class DAOFacade;
class IngredientDAO;
class IngredientListItemDAO;
class RecipeDAO;

class MealList : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<Meal> items READ items NOTIFY itemsChanged)
    Q_PROPERTY(Meal::Type type READ type NOTIFY neverNotify)
	Q_PROPERTY(qreal sumFat READ sumFat NOTIFY sumFatChanged)
	Q_PROPERTY(qreal sumProtein READ sumProtein NOTIFY sumProteinChanged)
	Q_PROPERTY(qreal sumCarbs READ sumCarbs NOTIFY sumCarbsChanged)
	Q_PROPERTY(qreal sumCalories READ sumCalories NOTIFY sumCaloriesChanged)
	Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY itemsChanged)
	Q_PROPERTY(bool selectionEmpty READ selectionEmpty NOTIFY selectionEmptyChanged)
	Q_PROPERTY(bool canImport READ canImport NOTIFY canImportChanged)

public:
	explicit MealList(QObject *parent = nullptr);
    ~MealList();

    static MealList *loadForDateAndType(QObject *parent, DAOFacade *facade, QDate d, Meal::Type type);

    QQmlListProperty<Meal> items();
    Meal::Type type() const { return m_type; }

    Q_INVOKABLE void createMeal(const QString &name);
    Q_INVOKABLE void createMealForIngredient(qint32 ingredientId);
	Q_INVOKABLE void createMealForRecipe(qint32 recipeId);
    Q_INVOKABLE void removeMeal(qint32 idx);
	Q_INVOKABLE bool createIngredientFromMeal(qint32 idx);
	Q_INVOKABLE bool createRecipeFromMeal(qint32 idx);

	bool createIngredientFromListItem(const IngredientListItemDAO *item);

	Q_INVOKABLE void clearSelection();
	Q_INVOKABLE bool selectionToRecipe(qint32 nameIdx = -1);
	Q_INVOKABLE bool copySelection(qint32 nameIdx = -1);
	Q_INVOKABLE bool recipeToIngredients(qint32 recipeIdx);
	Q_INVOKABLE bool importAsRecipe();
	Q_INVOKABLE bool importAsIngredients();

	qreal sumFat() const;
	qreal sumProtein() const;
	qreal sumCarbs() const;
	qreal sumCalories() const;

	bool isEmpty() const;
	bool selectionEmpty() const;

	bool canImport(bool recheck = false);
	Q_INVOKABLE void updateCanImport() {
		canImport(true);
	}

signals:
    void itemsChanged();
    void neverNotify();
	void sumFatChanged();
	void sumProteinChanged();
	void sumCarbsChanged();
	void sumCaloriesChanged();
	void selectionEmptyChanged();
	void canImportChanged();

private:
    static Meal *atFunc(QQmlListProperty<Meal> *p, int i);
    static int countFunc(QQmlListProperty<Meal> *p);
	void connectSignals(Meal *m);
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

	void updateMealFromIngredient(MealDAO *m, IngredientDAO *r, UpdateFields fields = UpdateField::All);
	void updateMealFromIngredientItem(MealDAO *m, const IngredientListItemDAO *r, UpdateFields fields = UpdateField::All);
	void updateMealFromRecipe(MealDAO *m, RecipeDAO *r, UpdateFields fields = UpdateField::All);
	bool tryConnectMealToIngredientByName(Meal *m, UpdateFields fields = UpdateField::All);

	QString processSelection(QList<Meal*> &sels, QList<int> &idxs, qint32 nameIdx, bool clear);

private:
    QList<Meal *> m_data;
    Meal::Type m_type;
    QDate m_date;
    DAOFacade *m_facade;
};

#endif // MEALLIST_H

