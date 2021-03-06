#ifndef INGREDIENTSTATSDBDAO_H
#define INGREDIENTSTATSDBDAO_H

#include "../ingredientstatsdao.h"
#include <QSqlRecord>

class IngredientStatsDbDAO : public IngredientStatsDAO
{
public:
	IngredientStatsDbDAO(const QSqlRecord &rec);

	qreal maxFat() const { return getData("maxFat"); }
	qreal minFat() const { return getData("minFat"); }
	qreal maxProtein() const { return getData("maxProtein"); }
	qreal minProtein() const { return getData("minProtein"); }
	qreal maxCarbs() const { return getData("maxCarbs"); }
	qreal minCarbs() const { return getData("minCarbs"); }
	qreal maxCalories() const { return getData("maxCalories"); }
	qreal minCalories() const { return getData("minCalories"); }

private:
	qreal getData(const QString &field) const;

private:
	QSqlRecord m_record;
};

#endif // INGREDIENTSTATSDBDAO_H
