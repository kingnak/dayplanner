#ifndef INGREDIENTSTATSDAO_H
#define INGREDIENTSTATSDAO_H

#include <QtGlobal>

class IngredientStatsDAO
{
public:
	virtual ~IngredientStatsDAO() {}

	virtual qreal maxFat() const = 0;
	virtual qreal minFat() const = 0;
	virtual qreal maxProtein() const = 0;
	virtual qreal minProtein() const = 0;
	virtual qreal maxCarbs() const = 0;
	virtual qreal minCarbs() const = 0;
	virtual qreal maxCalories() const = 0;
	virtual qreal minCalories() const = 0;
};

#endif // INGREDIENTSTATSDAO_H
