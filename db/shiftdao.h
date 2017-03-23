#ifndef SHIFTDAO_H
#define SHIFTDAO_H

#include <QDate>
#include "dbdaobase.h"

class DataBase;

class ShiftDAO : public DbDAOBase
{
public:
    ShiftDAO(QDate d, DataBase *db);

    int shiftIndex() const;
    void setShiftIndex(int idx);

protected:
    /*
    virtual bool doReset();
    virtual bool doLoad();
    virtual bool doInsert();
    virtual bool doUpdate();
    virtual bool doRemove();
    */
    virtual QStringList keyFields();
    virtual QString keyData(const QString &field);
    virtual QString tableName();

private:
    QDate m_date;
};

#endif // SHIFTDAO_H
