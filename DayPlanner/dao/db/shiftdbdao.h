#ifndef SHIFTDBDAO_H
#define SHIFTDBDAO_H

#include "dbdaobase.h"
#include "../shiftdao.h"
#include <QDate>

class DataBase;

class ShiftDbDAO : public ShiftDAO, private DbDAOBase
{
public:
    ShiftDbDAO(QDate d, DataBase *db);

    virtual QDate date() const;

    virtual int shiftIndex() const;
    virtual void setShiftIndex(int idx);

protected:
    virtual QStringList keyFields();
    virtual QString keyData(const QString &field);
    virtual QString tableName();

    DAO_USE(DbDAOBase)

	virtual void postReset();

private:
    QDate m_date;
};

#endif // SHIFTDBDAO_H
