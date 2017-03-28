
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

public:
    MealList(QObject *parent = nullptr);
    ~MealList();

    static MealList *loadForDateAndType(QObject *parent, DAOFacade *facade, QDate d, Meal::Type type);

    QQmlListProperty<Meal> items();
    Meal::Type type() const { return m_type; }

    Q_INVOKABLE void createMeal(const QString &name);

signals:
    void itemsChanged();
    void neverNotify();

private:
    static Meal *atFunc(QQmlListProperty<Meal> *p, int i);
    static int countFunc(QQmlListProperty<Meal> *p);

private:
    QList<Meal *> m_data;
    Meal::Type m_type;
    QDate m_date;
    DAOFacade *m_facade;
};

#endif // MEALLIST_H

