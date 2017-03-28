#include <QApplication>
#include <QQmlApplicationEngine>
#include "dayplannerqmlglobals.h"

//#define WITH_VLD
#ifdef WITH_VLD
#include <vld.h>
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DayPlannerQMLGlobals::registerTypes();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}