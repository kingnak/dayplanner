#ifndef TRAININGDAO_H
#define TRAININGDAO_H

#include "daobase.h"
#include <QString>

class TrainingDAO : public virtual DAOBase
{
public:
	virtual qint32 id() const = 0;

	virtual QString name() const = 0;
	virtual void setName(const QString &n) = 0;
};

#endif // TRAININGDAO_H
