#ifndef DAO_H
#define DAO_H

#include <QList>

class QDate;
class ShiftDAO;
class MealDAO;
class IngredientDAO;
class TrainingDAO;
class WorkoutDAO;
class IngredientStatsDAO;
class RecipeTemplateDAO;
class IngredientListItemDAO;
class IngredientListDAO;
class RecipeDAO;

class DAOFacade
{
public:
    virtual ~DAOFacade() {}

	virtual QStringList loadAllShifts() = 0;
    virtual ShiftDAO *loadShift(QDate d) = 0;

    virtual QList<MealDAO *> loadMeals(QDate d, qint32 type) = 0;
    virtual MealDAO *createMeal(QDate d, qint32 type) = 0;

    virtual IngredientDAO *loadIngredient(qint32 ingredientId) = 0;
	virtual QList<IngredientDAO *> loadIngredients() = 0;
	virtual IngredientDAO *createIngredient(const QString &name) = 0;
	virtual IngredientDAO *loadIngredientByName(const QString &name) = 0;
	virtual IngredientStatsDAO *loadIngredientStats() = 0;
	virtual bool removeIngredient(qint32 ingredientId) = 0;

	virtual QList<RecipeTemplateDAO *> loadRecipeTemplates() = 0;

	virtual QList<IngredientListItemDAO *> loadIngredientListItems(qint32 listId) = 0;

	virtual IngredientListDAO *createIngredientList() = 0;
	virtual IngredientListItemDAO * createIngredientListItem(qint32 listId) = 0;

	virtual RecipeDAO *createRecipe() = 0;
	virtual RecipeDAO *loadRecipe(qint32 recipeId) = 0;

	virtual TrainingDAO *loadTraining(qint32 trainingId) = 0;
	virtual QList<TrainingDAO *> loadTrainings() = 0;

	virtual QList<WorkoutDAO *> loadWorkouts(QDate d) = 0;
	virtual WorkoutDAO *createWorkout(QDate d) = 0;
};

DAOFacade *globalDAOFacade();

#endif // DAO_H
