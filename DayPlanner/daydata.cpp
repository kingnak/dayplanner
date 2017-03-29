#include "daydata.h"
#include "dao/dao.h"
#include "meallist.h"
#include "dao/db/shiftdbdao.h"

DayData::DayData(const QDate &d, DAOFacade *facade, QObject *parent)
:   QObject(parent),
    m_date(d),
    m_shift(facade->loadShift(d))
{
	m_meals << MealList::loadForDateAndType(this, facade, d, Meal::Breakfast)
			<< MealList::loadForDateAndType(this, facade, d, Meal::Lunch)
			<< MealList::loadForDateAndType(this, facade, d, Meal::Dinner);
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
