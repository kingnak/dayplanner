#include "dbdaofacade.h"
#include "database.h"
#include "shiftdbdao.h"
#include "mealdbdao.h"
#include <QtSql>

ShiftDAO *DbDAOFacade::loadShift(QDate d)
{
    return new ShiftDbDAO(d, &DataBase::instance());
}

QList<MealDAO *> DbDAOFacade::loadMeals(QDate d, qint32 type)
{
    QString query = QString("SELECT id FROM Meal WHERE date = '%1' AND type = %2 ORDER BY sort")
            .arg(d.toString("yyyy-MM-dd"))
            .arg(type);

    QSqlQuery q = DataBase::instance().executeQuery(query);

    QList<MealDAO *> ret;
    while (q.next()) {
        MealDAO *m = new MealDbDAO(q.record().value(0).toInt(), &DataBase::instance());
        ret << m;
    }

    return ret;
}

MealDAO *DbDAOFacade::createMeal(QDate d, qint32 type)
{
    MealDbDAO *m = new MealDbDAO(-1, &DataBase::instance());
    m->setDate(d);
    m->setType(type);

    QString query = QString("SELECT COUNT(*) FROM Meal WHERE date = '%1' AND type = %2")
            .arg(d.toString("yyyy-MM-dd"))
            .arg(type);

    QSqlQuery q = DataBase::instance().executeQuery(query);
    if (q.next()) {
        m->setSort(q.record().value(0).toInt() + 1);
    } else {
        m->setSort(1);
    }

    return m;
}
