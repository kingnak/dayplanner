#ifndef SHIFTDAO_H
#define SHIFTDAO_H

#include "daobase.h"

class QDate;

class DataBase;

class ShiftDAO : public virtual DAOBase
{
public:
    virtual QDate date() const = 0;

    virtual int shiftIndex() const = 0;
    virtual void setShiftIndex(int idx) = 0;
};

#endif // SHIFTDAO_H
