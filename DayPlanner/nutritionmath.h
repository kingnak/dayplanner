#ifndef NUTRITIONMATH_H
#define NUTRITIONMATH_H

#include <QtGlobal>

class NutritionMath
{
private:
	NutritionMath();
	Q_DISABLE_COPY(NutritionMath)

public:
	static qreal scaldemanRatio(qreal fat, qreal carbs, qreal protein);
};

#endif // NUTRITIONMATH_H
