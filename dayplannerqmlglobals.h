#ifndef DAYPLANNERQMLGLOBALS_H
#define DAYPLANNERQMLGLOBALS_H

#include <QObject>
#include "meal.h"

class DayPlannerQMLGlobals : public QObject
{
    Q_OBJECT
public:
    explicit DayPlannerQMLGlobals(QObject *parent = 0);
};

#endif // DAYPLANNERQMLGLOBALS_H
