#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "dayplannerqmlglobals.h"
#include "dao/db/database.h"

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
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
