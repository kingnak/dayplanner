#ifndef DBAUTOIDDAOBASE_H
#define DBAUTOIDDAOBASE_H

#include "dbdaobase.h"

class DbAutoIdDAOBase : public DbDAOBase
{
public:
    DbAutoIdDAOBase(DataBase *db, qint32 id = -1, DAOBase::State s = DAOBase::New);

protected:
    qint32 id() const;
    bool doInsert();
    QStringList keyFields();
    QString keyData(const QString &field);

protected:
    qint32 m_id;
};

#endif // DBAUTOIDDAOBASE_H
