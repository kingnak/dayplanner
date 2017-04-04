
#ifndef MEALLIST_H
#define MEALLIST_H

#include <QObject>
#include <QDate>
#include <QQmlListProperty>
#include "meal.h"

class DAOFacade;

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

public:
	explicit MealList(QObject *parent = nullptr);
    ~MealList();

    static MealList *loadForDateAndType(QObject *parent, DAOFacade *facade, QDate d, Meal::Type type);

    QQmlListProperty<Meal> items();
    Meal::Type type() const { return m_type; }

    Q_INVOKABLE void createMeal(const QString &name);
    Q_INVOKABLE void createMealForRecipe(qint32 recipeId);
    Q_INVOKABLE void removeMeal(qint32 idx);

	qreal sumFat() const;
	qreal sumProtein() const;
	qreal sumCarbs() const;
	qreal sumCalories() const;

	bool isEmpty() const;

signals:
    void itemsChanged();
    void neverNotify();
	void sumFatChanged();
	void sumProteinChanged();
	void sumCarbsChanged();
	void sumCaloriesChanged();

private:
    static Meal *atFunc(QQmlListProperty<Meal> *p, int i);
    static int countFunc(QQmlListProperty<Meal> *p);
	void connectSignals(Meal *m);
	void notifySumsChanged();

private:
    QList<Meal *> m_data;
    Meal::Type m_type;
    QDate m_date;
    DAOFacade *m_facade;
};

#endif // MEALLIST_H

