#include "mealdao.h"

qreal MealDAO::calcFat() const
{
    return static_cast<qreal>(fat()) * factor();
}
