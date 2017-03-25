#include "meallist.h"
#include "db/database.h"
#include "db/mealdao.h"
#include <QtSql>

MealList::MealList(QObject *parent)
    : QObject(parent)
{
    //m_list = new QQmlListProperty<Meal>(this, this, MealList::appendFunc, MealList::countFunc, MealList::atFunc, MealList::clearFunc);
    m_list = new QQmlListProperty<Meal>(this, this, MealList::countFunc, MealList::atFunc);
}

MealList::~MealList()
{
    delete m_list;
}

MealList *MealList::loadForDateAndType(QObject *parent, QDate d, int type)
{
    QString query = QString("SELECT id FROM Meal WHERE date = '%1' AND type = %2")
            .arg(d.toString("yyyy-MM-dd"))
            .arg(type);

    QSqlQuery q = DataBase::instance().executeQuery(query);

    MealList *ret = new MealList(parent);
    ret->m_type = type;
    ret->m_date = d;
    while (q.next()) {
        Meal *m = new Meal(new MealDAO(q.record().value(0).toInt(), &DataBase::instance()), ret);
        ret->m_data << m;
    }

    return ret;
}

QQmlListProperty<Meal> MealList::items()
{
    return *m_list;
}

void MealList::createMeal(const QString &name)
{
    MealDAO *m = new MealDAO(-1, &DataBase::instance());
    m->setName(name);
    m->setDate(m_date);
    m->setType(static_cast<MealDAO::Type> (m_type));
    if (m->save()) {
        m_data.append(new Meal(m, this));
        emit itemsChanged();
    } else {
        delete m;
    }
}

Meal *MealList::atFunc(QQmlListProperty<Meal> *p, int i)
{
    return static_cast<MealList *> (p->data)->m_data.at(i);
}

int MealList::countFunc(QQmlListProperty<Meal> *p)
{
    return static_cast<MealList*> (p->data)->m_data.count();
}
/*
void MealList::appendFunc(QQmlListProperty<Meal> *p, Meal *m)
{
    static_cast<MealList*> (p->data)->m_data.append(m);
}

void MealList::clearFunc(QQmlListProperty<Meal> *p)
{
    static_cast<MealList*> (p->data)->m_data.clear();
}
*/
