#include "dayplannerqmlglobals.h"
#include <QQmlApplicationEngine>

#include "dao/dao.h"
#include "dao/db/dbdaofacade.h"
#include "daymodel.h"
#include "meal.h"
#include "meallist.h"
#include "recipelist.h"
#include "qmlutils.h"
#include "shiftlist.h"
#include "traininglist.h"
#include "workout.h"
#include "workoutlist.h"

DayPlannerQMLGlobals::DayPlannerQMLGlobals(QObject *parent) : QObject(parent)
{
}

void DayPlannerQMLGlobals::registerTypes()
{
    qRegisterMetaType<Meal::Type>("Meal::Type");
    qmlRegisterType<DayModel>("org.kingnak.dayplanner", 1, 0, "DayModel");
    qmlRegisterType<Meal>("org.kingnak.dayplanner", 1, 0, "Meal");
    qmlRegisterType<MealList>("org.kingnak.dayplanner", 1, 0, "MealList");
    qmlRegisterType<RecipeList>("org.kingnak.dayplanner", 1, 0, "RecipeModel");
	qmlRegisterType<QmlUtils>("org.kingnak.dayplanner", 1, 0, "Utils");
	qmlRegisterType<ShiftList>("org.kingnak.dayplanner", 1, 0, "ShiftModel");
	qmlRegisterType<TrainingList>("org.kingnak.dayplanner", 1, 0, "TrainingModel");
	qmlRegisterType<Workout>("org.kingnak.dayplanner", 1, 0, "Workout");
	qmlRegisterType<WorkoutList>("org.kingnak.dayplanner", 1, 0, "WorkoutList");
}

DAOFacade *globalDAOFacade() {
    static DbDAOFacade inst_;
    return &inst_;
}
