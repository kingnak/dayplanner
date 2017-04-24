#include "dayplannerqmlglobals.h"
#include <QQmlApplicationEngine>

#include "dao/dao.h"
#include "dao/db/dbdaofacade.h"
#include "daymodel.h"
#include "meal.h"
#include "meallist.h"
#include "ingredientlist.h"
#include "qmlutils.h"
#include "shiftlist.h"
#include "traininglist.h"
#include "workout.h"
#include "workoutlist.h"
#include "recipetemplatelist.h"
#include "ingrecuniformmodel.h"

DayPlannerQMLGlobals::DayPlannerQMLGlobals(QObject *parent) : QObject(parent)
{
}

void DayPlannerQMLGlobals::registerTypes()
{
    qRegisterMetaType<Meal::Type>("Meal::Type");
	qmlRegisterUncreatableType<DayModel>("org.kingnak.dayplanner", 1, 0, "DayModel", "");
    qmlRegisterType<Meal>("org.kingnak.dayplanner", 1, 0, "Meal");
    qmlRegisterType<MealList>("org.kingnak.dayplanner", 1, 0, "MealList");
	qmlRegisterUncreatableType<IngredientList>("org.kingnak.dayplanner", 1, 0, "IngredientModel", "");
	qmlRegisterType<QmlUtils>("org.kingnak.dayplanner", 1, 0, "Utils");
	qmlRegisterUncreatableType<ShiftList>("org.kingnak.dayplanner", 1, 0, "ShiftModel", "");
	qmlRegisterUncreatableType<TrainingList>("org.kingnak.dayplanner", 1, 0, "TrainingModel", "");
	qmlRegisterUncreatableType<RecipeTemplateList>("org.kingnak.dayplanner", 1, 0, "RecipeTemplateModel", "");
	qmlRegisterUncreatableType<IngRecUniformModel>("org.kingnak.dayplanner", 1, 0, "UniformRecipeIngredientModel", "");
	qmlRegisterType<Workout>("org.kingnak.dayplanner", 1, 0, "Workout");
	qmlRegisterType<WorkoutList>("org.kingnak.dayplanner", 1, 0, "WorkoutList");
}

DAOFacade *globalDAOFacade() {
    static DbDAOFacade inst_;
    return &inst_;
}
