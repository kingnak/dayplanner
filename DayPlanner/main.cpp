#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "dayplannerqmlglobals.h"
#include "dao/db/database.h"
#include "shiftlist.h"
#include "traininglist.h"
#include "ingredientlist.h"
#include "daymodel.h"
#include "recipetemplatelist.h"
#include "ingrecuniformmodel.h"
#include "recipe.h"

//#define WITH_VLD
#ifdef WITH_VLD
#include <vld.h>
#endif

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	if (app.arguments().value(1) == "--fill-default-ingredients") {
		DataBase::instance().fillDefaultIngredients();
	}

    DayPlannerQMLGlobals::registerTypes();

    QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("shiftsModel", new ShiftList);
	engine.rootContext()->setContextProperty("trainingModel", new TrainingList);
	auto i = new IngredientList;
	engine.rootContext()->setContextProperty("ingredientModel", i);
	engine.rootContext()->setContextProperty("dayModel", new DayModel);
	auto r = new RecipeTemplateList;
	engine.rootContext()->setContextProperty("recipeTemplateModel", r);
	engine.rootContext()->setContextProperty("uniformModel", new IngRecUniformModel(r, i));
	engine.rootContext()->setContextProperty("recipeModel", RecipeLoader::instance());


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
