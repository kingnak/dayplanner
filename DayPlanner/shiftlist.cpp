#include "shiftlist.h"
#include "dao/dao.h"

ShiftList::ShiftList()
{

}

QStringList ShiftList::shiftList()
{
	if (m_shifts.isEmpty()) {
		m_shifts = globalDAOFacade()->loadAllShifts();
	}
	return m_shifts;
}
