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

    virtual IngredientDAO *loadIngredient(qint32 ingredientId);
	virtual QList<IngredientDAO *> loadIngredients();
	virtual IngredientDAO *createIngredient(const QString &name);
	virtual IngredientDAO *loadIngredientByName(const QString &name);
	virtual IngredientStatsDAO *loadIngredientStats();
	virtual bool removeIngredient(qint32 ingredientId);

	virtual QList<RecipeTemplateDAO *> loadRecipeTemplates();

	virtual IngredientListDAO *createIngredientList();
	virtual IngredientListItemDAO *createIngredientListItem(qint32 listId);

	virtual RecipeDAO *createRecipe();
	virtual RecipeDAO *loadRecipe(qint32 recipeId);

	virtual bool removeRecipe(qint32 recipeId);
	virtual bool removeIngredientList(qint32 ingredientListId);

	virtual QList<IngredientListItemDAO *> loadIngredientListItems(qint32 listId);

	virtual TrainingDAO *loadTraining(qint32 trainingId);
	virtual QList<TrainingDAO *> loadTrainings();

	virtual QList<WorkoutDAO *> loadWorkouts(QDate d);
	virtual WorkoutDAO *createWorkout(QDate d);
};

#endif // DBDAOFACADE_H
