#ifndef DAO_H
#define DAO_H

#include <QList>

class QDate;
class ShiftDAO;
class MealDAO;
class RecipeDAO;
class TrainingDAO;
class WorkoutDAO;

class DAOFacade
{
public:
    virtual ~DAOFacade() {}

	virtual QStringList loadAllShifts() = 0;
    virtual ShiftDAO *loadShift(QDate d) = 0;

    virtual QList<MealDAO *> loadMeals(QDate d, qint32 type) = 0;
    virtual MealDAO *createMeal(QDate d, qint32 type) = 0;

    virtual RecipeDAO *loadRecipe(qint32 recipeId) = 0;
    virtual QList<RecipeDAO *> loadRecipes() = 0;
	virtual RecipeDAO *createRecipe(const QString &name) = 0;
	virtual RecipeDAO *loadRecipeByName(const QString &name) = 0;

	virtual TrainingDAO *loadTraining(qint32 trainingId) = 0;
	virtual QList<TrainingDAO *> loadTrainings() = 0;

	virtual QList<WorkoutDAO *> loadWorkouts(QDate d) = 0;
	virtual WorkoutDAO *createWorkout(QDate d) = 0;
};

DAOFacade *globalDAOFacade();

#endif // DAO_H
