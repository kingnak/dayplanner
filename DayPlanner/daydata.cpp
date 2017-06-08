#include "daydata.h"
#include "dao/dao.h"
#include "meallist.h"
#include "dao/shiftdao.h"
#include "workoutlist.h"

DayData::DayData(const QDate &d, DAOFacade *facade, QObject *parent)
:   QObject(parent),
    m_date(d),
    m_shift(facade->loadShift(d))
{
	m_meals << MealList::loadForDateAndType(this, facade, d, Meal::Breakfast)
			<< MealList::loadForDateAndType(this, facade, d, Meal::Lunch)
			<< MealList::loadForDateAndType(this, facade, d, Meal::Dinner)
			<< MealList::loadForDateAndType(this, facade, d, Meal::Snacks);

	m_workout = WorkoutList::loadForDate(this, facade, d);

	for (auto m : m_meals) {
		connect(m, &MealList::sumFatChanged, this, &DayData::sumsChanged);
		connect(m, &MealList::sumProteinChanged, this, &DayData::sumsChanged);
		connect(m, &MealList::sumCarbsChanged, this, &DayData::sumsChanged);
		connect(m, &MealList::sumCaloriesChanged, this, &DayData::sumsChanged);
	}
}

DayData::~DayData()
{
    delete m_shift;
}

int DayData::shiftIndex() const
{
    int r = m_shift->shiftIndex();
    return r;
}

void DayData::setShiftIndex(int i)
{
    if (m_shift->shiftIndex() != i) {
        if (i) {
            m_shift->setShiftIndex(i);
            if (m_shift->save()) {
                emit shiftIndexChanged(i);
            }
        } else {
            if (m_shift->remove()) {
                emit shiftIndexChanged(i);
            }
        }
    }
}

MealList *DayData::breakfast() const
{
	return m_meals[0];
}

MealList *DayData::lunch() const
{
	return m_meals[1];
}

MealList *DayData::dinner() const
{
	return m_meals[2];
}

MealList *DayData::snack() const
{
	return m_meals[3];
}

WorkoutList *DayData::workout() const
{
	return m_workout;
}

qreal DayData::sumFat() const
{
	qreal s = 0;
	for (MealList *m : m_meals) {
		s += m->sumFat();
	}
	return s;
}

qreal DayData::sumProtein() const
{
	qreal s = 0;
	for (MealList *m : m_meals) {
		s += m->sumProtein();
	}
	return s;
}

qreal DayData::sumCarbs() const
{
	qreal s = 0;
	for (MealList *m : m_meals) {
		s += m->sumCarbs();
	}
	return s;
}

qreal DayData::sumCalories() const
{
	qreal s = 0;
	for (MealList *m : m_meals) {
		s += m->sumCalories();
	}
	return s;
}

bool DayData::hasDisplayData() const
{
	for (MealList *m : m_meals) {
		if (!m->isEmpty()) return true;
	}
	return false;
}
