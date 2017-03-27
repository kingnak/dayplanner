#include "meal.h"
#include "dao/mealdao.h"

Meal::Meal(QObject *parent)
    : QObject(parent),
      m_meal(nullptr)
{
    Q_ASSERT(false);
}

Meal::Meal(MealDAO *meal, QObject *parent)
    : QObject(parent),
      m_meal(meal)
{
}

Meal::~Meal()
{
    delete m_meal;
}

Meal::Type Meal::type() const
{
    if (m_meal) return static_cast<Type> (m_meal->type());
    return Meal::Type::Other;
}

QString Meal::name() const
{
    if (m_meal) return m_meal->name();
    return "";
}

void Meal::setName(const QString &n)
{
    if (n != name()) {
        if (m_meal) {
            m_meal->setName(n);
            if (m_meal->save()) {
                emit nameChanged(n);
            }
        }
    }
}

qint32 Meal::fat() const
{
    if (m_meal) return m_meal->fat();
    return 0;
}

void Meal::setFat(const qint32 f)
{
    if (f != fat()) {
        if (m_meal) {
            m_meal->setFat(f);
            if (m_meal->save()) {
                emit fatChanged();
            }
        }
    }
}

qreal Meal::calcFat() const
{
    if (m_meal) return m_meal->calcFat();
    return 0;
}
