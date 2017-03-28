#ifndef MEAL_H
#define MEAL_H

#include <QObject>
#include "dao/mealdao.h"

class Meal : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Type type READ type)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(qreal calcFat READ calcFat NOTIFY fatChanged)
    Q_PROPERTY(qint32 fat READ fat WRITE setFat NOTIFY fatChanged)
    Q_PROPERTY(qreal calcProtein READ calcProtein NOTIFY proteinChanged)
    Q_PROPERTY(qint32 protein READ protein WRITE setProtein NOTIFY proteinChanged)
    Q_PROPERTY(qreal calcCarbs READ calcCarbs NOTIFY carbsChanged)
    Q_PROPERTY(qint32 carbs READ carbs WRITE setCarbs NOTIFY carbsChanged)
    Q_PROPERTY(qreal calcCalories READ calcCalories NOTIFY caloriesChanged)
    Q_PROPERTY(qint32 calories READ calories WRITE setCalories NOTIFY caloriesChanged)

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

    QString name() const;
    void setName(const QString &n);

    qint32 fat() const;
    void setFat(const qint32 f);

    qint32 protein() const;
    void setProtein(const qint32 p);

    qint32 carbs() const;
    void setCarbs(qint32 c);

    qint32 calories() const;
    void setCalories(qint32 c);

    qreal calcFat() const;
    qreal calcProtein() const;
    qreal calcCarbs() const;
    qreal calcCalories() const;

signals:
    void nameChanged(const QString &n);
    void fatChanged();
    void proteinChanged();
    void carbsChanged();
    void caloriesChanged();

private:
    MealDAO *m_meal;
};

#endif // MEAL_H
