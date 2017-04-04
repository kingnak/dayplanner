#ifndef WORKOUTDAO_H
#define WORKOUTDAO_H

#include "daobase.h"
#include <QDate>

class WorkoutDAO : public virtual DAOBase
{
public:
	virtual QString name() const = 0;
	virtual void setName(const QString &name) = 0;

	virtual QString info() const = 0;
	virtual void setInfo(const QString &info) = 0;

	virtual QDate date() const = 0;
	virtual void setDate(QDate d) = 0;

	virtual qint32 trainingId() const = 0;
	virtual void setTrainingId(qint32 id) = 0;
};

#endif // WORKOUTDAO_H
