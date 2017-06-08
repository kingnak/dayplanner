#include "nutritionmath.h"


qreal NutritionMath::scaldemanRatio(qreal fat, qreal carbs, qreal protein)
{
	if (carbs+protein < 0.1) return 1.;
	return fat / (carbs+protein);
}
