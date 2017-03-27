#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "dayplannerqmlglobals.h"

//#define WITH_VLD
#ifdef WITH_VLD
#include <vld.h>
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DayPlannerQMLGlobals globals;
    Q_UNUSED(globals)

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
