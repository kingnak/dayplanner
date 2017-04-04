#ifndef WORKOUTDBDAO_H
#define WORKOUTDBDAO_H

#include "../workoutdao.h"
#include "dbautoiddaobase.h"

class WorkoutDbDAO : public WorkoutDAO, private DbAutoIdDAOBase
{
public:
	WorkoutDbDAO(qint32 id, DataBase *db);

	QString name() const;
	void setName(const QString &name);

	QString info() const;
	void setInfo(const QString &info);

	QDate date() const;
	void setDate(QDate d);

	qint32 trainingId() const;
	void setTrainingId(qint32 id);

	qint32 sort() const;
	void setSort(qint32 sort);

	DAO_USE(DbAutoIdDAOBase)

protected:
	virtual QStringList orderFields();
	virtual QString tableName();
};

#endif // WORKOUTDBDAO_H
