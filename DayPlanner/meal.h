#ifndef MEAL_H
#define MEAL_H

#include <QObject>
#include "dao/mealdao.h"

class Meal : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Type type READ type)
	Q_PROPERTY(qint32 ingredientId READ ingredientId WRITE setIngredientId NOTIFY ingredientIdChanged)
	Q_PROPERTY(qint32 recipeId READ recipeId WRITE setRecipeId NOTIFY recipeIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(qint32 quantity READ quantity WRITE setQuantity NOTIFY quantityChanged)
	Q_PROPERTY(qreal calcFat READ calcFat WRITE updateFat NOTIFY fatChanged)
    Q_PROPERTY(qreal fat READ fat WRITE setFat NOTIFY fatChanged)
	Q_PROPERTY(qreal calcProtein READ calcProtein WRITE updateProtein NOTIFY proteinChanged)
    Q_PROPERTY(qreal protein READ protein WRITE setProtein NOTIFY proteinChanged)
	Q_PROPERTY(qreal calcCarbs READ calcCarbs WRITE updateCarbs NOTIFY carbsChanged)
    Q_PROPERTY(qreal carbs READ carbs WRITE setCarbs NOTIFY carbsChanged)
	Q_PROPERTY(qreal calcCalories READ calcCalories WRITE updateCalories NOTIFY caloriesChanged)
    Q_PROPERTY(qreal calories READ calories WRITE setCalories NOTIFY caloriesChanged)
	Q_PROPERTY(bool isConnectedToIngredient READ isConnectedToIngredient NOTIFY ingredientIdChanged)
	Q_PROPERTY(bool isConnectedToRecipe READ isConnectedToRecipe NOTIFY recipeIdChanged)
	Q_PROPERTY(bool isConnected READ isConnected NOTIFY connectedChanged)

public:
    explicit Meal(QObject *parent = 0);
    explicit Meal(MealDAO *meal, QObject *parent = 0);
    ~Meal();

    enum Type {
        Breakfast = 1,
        Lunch,
        Dinner,
        Snacks,
        Other
    };
    Q_ENUM(Type)

    Type type() const;

    bool erase();

    QString name() const;
    void setName(const QString &n);

	qint32 quantity() const;
	void setQuantity(qint32 f);

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

	qint32 ingredientId() const;
	void setIngredientId(qint32 id);
	bool isConnectedToIngredient() const;

	qint32 recipeId() const;
	void setRecipeId(qint32 id);
	bool isConnectedToRecipe() const;

	bool isConnected() const;

signals:
	void nameChanged();
    void quantityChanged();
    void fatChanged();
    void proteinChanged();
    void carbsChanged();
    void caloriesChanged();
	void ingredientIdChanged();
	void recipeIdChanged();
	void connectedChanged();

private:
	void notifyValuesChanged();

private:
    MealDAO *m_meal;

	friend class MealList;
};

#endif // MEAL_H
