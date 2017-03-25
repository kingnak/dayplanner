#include "daydata.h"

DayData::DayData(const QDate &d, DAOFacade *facade, QObject *parent)
:   QObject(parent),
    m_date(d),
    m_shift(d, facade)
{
    m_breakfast = MealList::loadForDateAndType(this, d, 1);
}

int DayData::shiftIndex() const
{
    int r = m_shift.shiftIndex();
    return r;
}

void DayData::setShiftIndex(int i)
{
    if (m_shift.shiftIndex() != i) {
        if (i) {
            m_shift.setShiftIndex(i);
            if (m_shift.save()) {
                emit shiftIndexChanged(i);
            }
        } else {
            if (m_shift.remove()) {
                emit shiftIndexChanged(i);
            }
        }
    }
}

MealList *DayData::breakfast() const
{
    return m_breakfast;
}
