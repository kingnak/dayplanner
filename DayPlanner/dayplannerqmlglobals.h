#ifndef DAYPLANNERQMLGLOBALS_H
#define DAYPLANNERQMLGLOBALS_H

#include <QObject>
#include "meal.h"

class DayPlannerQMLGlobals : public QObject
{
    Q_OBJECT
    explicit DayPlannerQMLGlobals(QObject *parent = 0);
public:
    static void registerTypes();
};

#endif // DAYPLANNERQMLGLOBALS_H
