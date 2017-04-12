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
	virtual RecipeDAO *createRecipe(const QString &name);
	virtual RecipeDAO *loadRecipeByName(const QString &name);

	virtual TrainingDAO *loadTraining(qint32 trainingId);
	virtual QList<TrainingDAO *> loadTrainings();

	virtual QList<WorkoutDAO *> loadWorkouts(QDate d);
	virtual WorkoutDAO *createWorkout(QDate d);
};

#endif // DBDAOFACADE_H
