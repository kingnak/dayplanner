#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "daymodel.h"
#include "meal.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<DayModel>("org.kingnak.dayplanner", 1, 0, "DayModel");
    qmlRegisterType<Meal>("org.kingnak.dayplanner", 1, 0, "Meal");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
