#include "dayplannerqmlglobals.h"
#include <QQmlApplicationEngine>

#include "daymodel.h"
#include "meal.h"
#include "meallist.h"

DayPlannerQMLGlobals::DayPlannerQMLGlobals(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<Meal::Type>("Meal::Type");
    qmlRegisterType<DayModel>("org.kingnak.dayplanner", 1, 0, "DayModel");
    qmlRegisterType<Meal>("org.kingnak.dayplanner", 1, 0, "Meal");
    qmlRegisterType<MealList>("org.kingnak.dayplanner", 1, 0, "MealList");
}
