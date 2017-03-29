#ifndef DAO_H
#define DAO_H

#include <QList>

class QDate;
class ShiftDAO;
class MealDAO;
class RecipeDAO;

class DAOFacade
{
public:
    virtual ~DAOFacade() {}

    virtual ShiftDAO *loadShift(QDate d) = 0;
    virtual QList<MealDAO *> loadMeals(QDate d, qint32 type) = 0;
    virtual MealDAO *createMeal(QDate d, qint32 type) = 0;

    virtual RecipeDAO *loadRecipe(qint32 recipeId) = 0;
    virtual QList<RecipeDAO *> loadRecipes() = 0;
};

DAOFacade *globalDAOFacade();

#endif // DAO_H
