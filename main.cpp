#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "daymodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<DayModel>("org.kingnak.dayplanner", 1, 0, "DayModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
