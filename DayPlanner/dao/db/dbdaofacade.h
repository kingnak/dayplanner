#ifndef DBDAOFACADE_H
#define DBDAOFACADE_H

#include "../dao.h"

class DbDAOFacade : public DAOFacade
{
public:
    virtual ShiftDAO *loadShift(QDate d);
	virtual QStringList loadAllShifts();

    virtual QList<MealDAO *> loadMeals(QDate d, qint32 type);
    virtual MealDAO *createMeal(QDate d, qint32 type);

    virtual RecipeDAO *loadRecipe(qint32 recipeId);
    virtual QList<RecipeDAO *> loadRecipes();
};

#endif // DBDAOFACADE_H
