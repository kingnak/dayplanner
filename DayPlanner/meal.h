#ifndef MEAL_H
#define MEAL_H

#include <QObject>
#include "dao/mealdao.h"

class Meal : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Type type READ type)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(qreal factor READ factor WRITE setFactor NOTIFY factorChanged)
    Q_PROPERTY(QString calcFat READ calcFat WRITE updateFat NOTIFY fatChanged)
    Q_PROPERTY(qreal fat READ fat WRITE setFat NOTIFY fatChanged)
    Q_PROPERTY(QString calcProtein READ calcProtein WRITE updateProtein NOTIFY proteinChanged)
    Q_PROPERTY(qreal protein READ protein WRITE setProtein NOTIFY proteinChanged)
    Q_PROPERTY(QString calcCarbs READ calcCarbs WRITE updateCarbs NOTIFY carbsChanged)
    Q_PROPERTY(qreal carbs READ carbs WRITE setCarbs NOTIFY carbsChanged)
    Q_PROPERTY(QString calcCalories READ calcCalories WRITE updateCalories NOTIFY caloriesChanged)
    Q_PROPERTY(qreal calories READ calories WRITE setCalories NOTIFY caloriesChanged)

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

    qreal factor() const;
    void setFactor(qreal f);

    qreal fat() const;
    void setFat(qreal f);
    QString calcFat() const;
    void updateFat(QString f);

    qreal protein() const;
    void setProtein(qreal p);
    QString calcProtein() const;
    void updateProtein(QString p);

    qreal carbs() const;
    void setCarbs(qreal c);
    QString calcCarbs() const;
    void updateCarbs(QString c);

    qreal calories() const;
    void setCalories(qreal c);
    QString calcCalories() const;
    void updateCalories(QString c);

private:
    static QString formatNumber(qreal q);
    bool updateNumber(const QString &n, qreal f, void (Meal::*setter)(qreal), void (Meal::*emitter)());

signals:
    void nameChanged(const QString &n);
    void factorChanged();
    void fatChanged();
    void proteinChanged();
    void carbsChanged();
    void caloriesChanged();

private:
    MealDAO *m_meal;
};

#endif // MEAL_H
