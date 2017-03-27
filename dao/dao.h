#ifndef DAO_H
#define DAO_H

#include <QList>

class QDate;
class ShiftDAO;
class MealDAO;

class DAOFacade
{
public:
    virtual ~DAOFacade() {}

    virtual ShiftDAO *loadShift(QDate d) = 0;
    virtual QList<MealDAO *> loadMeals(QDate d, qint32 type) = 0;
    virtual MealDAO *createMeal(QDate d, qint32 type) = 0;
};

#endif // DAO_H
