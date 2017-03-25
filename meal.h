#ifndef MEAL_H
#define MEAL_H

#include <QObject>

class MealDAO;

class Meal : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int type READ type)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(qreal calcFat READ calcFat NOTIFY fatChanged)
    Q_PROPERTY(qint32 fat READ fat WRITE setFat NOTIFY fatChanged)

public:
    explicit Meal(QObject *parent = 0);
    explicit Meal(MealDAO *meal, QObject *parent = 0);
    ~Meal();

    int type() const;

    QString name() const;
    void setName(const QString &n);

    qint32 fat() const;
    void setFat(const qint32 f);

    qreal calcFat() const;

signals:
    void nameChanged(const QString &n);
    void fatChanged();

private:
    MealDAO *m_meal;
};

#endif // MEAL_H
