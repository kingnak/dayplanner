
#ifndef MEALLIST_H
#define MEALLIST_H

#include <QObject>
#include <QDate>
#include <QQmlListProperty>
#include "meal.h"

class MealList : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<Meal> items READ items NOTIFY itemsChanged)
    Q_PROPERTY(int type READ type NOTIFY neverNotify)

public:
    MealList(QObject *parent = nullptr);
    ~MealList();
    static MealList *loadForDateAndType(QObject *parent, QDate d, int type);

    QQmlListProperty<Meal> items();
    int type() const { return m_type; }

    Q_INVOKABLE void createMeal(const QString &name);

signals:
    void itemsChanged();
    void neverNotify();

private:
    static Meal *atFunc(QQmlListProperty<Meal> *p, int i);
    static int countFunc(QQmlListProperty<Meal> *p);
    //static void appendFunc(QQmlListProperty<Meal> *p, Meal *m);
    //static void clearFunc(QQmlListProperty<Meal> *p);

private:
    QQmlListProperty<Meal> *m_list;
    QList<Meal *> m_data;
    int m_type;
    QDate m_date;
};

#endif // MEALLIST_H

