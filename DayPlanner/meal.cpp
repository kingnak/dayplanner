#include "meal.h"
#include "dao/mealdao.h"
#include <QLocale>

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
    return static_cast<Type> (m_meal->type());
}

bool Meal::erase()
{
    return m_meal->remove();
}

QString Meal::name() const
{
    return m_meal->name();
}

void Meal::setName(const QString &n)
{
    if (n != name()) {
        m_meal->setName(n);
        if (m_meal->save()) {
            emit nameChanged(n);
        }
    }
}

qreal Meal::factor() const
{
    qreal f = m_meal->factor();
    if (qFuzzyIsNull(f)) return 1;
    return f;
}

void Meal::setFactor(qreal f)
{
    if (f != factor()) {
        m_meal->setFactor(f);
        if (m_meal->save()) {
            emit factorChanged();
            emit fatChanged();
            emit proteinChanged();
            emit carbsChanged();
            emit caloriesChanged();
        }
    }
}

qreal Meal::fat() const
{
    return m_meal->fat();
}

void Meal::setFat(qreal f)
{
    if (f != fat()) {
        m_meal->setFat(f);
        if (m_meal->save()) {
            emit fatChanged();
        }
    }
}

QString Meal::calcFat() const
{
    return formatNumber(fat() * factor());
}

void Meal::updateFat(QString f)
{
    updateNumber(f, factor(), &Meal::setFat, &Meal::fatChanged);
}

qreal Meal::protein() const
{
    return m_meal->protein();
}

void Meal::setProtein(qreal p)
{
    if (p != protein()) {
        m_meal->setProtein(p);
        if (m_meal->save()) {
            emit proteinChanged();
        }
    }
}

QString Meal::calcProtein() const
{
    return formatNumber(protein() * factor());
}

void Meal::updateProtein(QString p)
{
    updateNumber(p, factor(), &Meal::setProtein, &Meal::proteinChanged);
}

qreal Meal::carbs() const
{
    return m_meal->carbs();
}

void Meal::setCarbs(qreal c)
{
    if (c != carbs()) {
        m_meal->setCarbs(c);
        if (m_meal->save()) {
            emit carbsChanged();
        }
    }
}

QString Meal::calcCarbs() const
{
    return formatNumber(carbs() * factor());
}

void Meal::updateCarbs(QString c)
{
    updateNumber(c, factor(), &Meal::setCarbs, &Meal::carbsChanged);
}

qreal Meal::calories() const
{
    return m_meal->calories();
}

void Meal::setCalories(qreal c)
{
    if (c != calories()) {
        m_meal->setCalories(c);
        if (m_meal->save()) {
            emit caloriesChanged();
        }
    }
}

QString Meal::calcCalories() const
{
    return formatNumber(calories() * factor());
}

void Meal::updateCalories(QString c)
{
    updateNumber(c, factor(), &Meal::setCalories, &Meal::caloriesChanged);
}

QString Meal::formatNumber(qreal q)
{
    QLocale l;
    QString ret = l.toString(q, 'f', 1);
    int pos = ret.indexOf(l.decimalPoint());
    if (pos >= 0) {
        if (ret.mid(pos+1) == "0") {
            ret = ret.left(pos);
        }
    }
    return ret;
}

bool Meal::updateNumber(const QString &n, qreal f, void (Meal::*setter)(qreal), void (Meal::*emitter)())
{
    bool ok;
    if (qFuzzyIsNull(f)) f = 1;
    qreal q = QLocale().toDouble(n, &ok);
    if (ok) {
        if (setter) (this->*setter)(q / f);
    } else {
        if (emitter) (this->*emitter)();
    }
    return ok;
}
