#ifndef TRAININGDBDAO_H
#define TRAININGDBDAO_H

#include "dbautoiddaobase.h"
#include "../trainingdao.h"

class TrainingDbDAO : public TrainingDAO, private DbAutoIdDAOBase
{
public:
	TrainingDbDAO(qint32 id, DataBase *db);

	virtual qint32 id() const;

	virtual QString name() const;
	virtual void setName(const QString &n);

	DAO_USE(DbAutoIdDAOBase)

protected:
	virtual QStringList orderFields();
	virtual QString tableName();
};

#endif // TRAININGDBDAO_H
