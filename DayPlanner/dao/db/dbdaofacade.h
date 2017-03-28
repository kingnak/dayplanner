#ifndef DBDAOFACADE_H
#define DBDAOFACADE_H

#include "../dao.h"

class DbDAOFacade : public DAOFacade
{
public:
    virtual ShiftDAO *loadShift(QDate d);
    virtual QList<MealDAO *> loadMeals(QDate d, qint32 type);
    virtual MealDAO *createMeal(QDate d, qint32 type);
};

#endif // DBDAOFACADE_H