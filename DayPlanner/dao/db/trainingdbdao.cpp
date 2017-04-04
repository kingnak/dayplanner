#include "trainingdbdao.h"

TrainingDbDAO::TrainingDbDAO(qint32 id, DataBase *db)
	: DbAutoIdDAOBase(db, id)
{
	load();
}

qint32 TrainingDbDAO::id() const
{
	return DbAutoIdDAOBase::id();
}

QString TrainingDbDAO::name() const
{
	return data<QString>("name");
}

void TrainingDbDAO::setName(const QString &n)
{
	setData("name", n);
}

QStringList TrainingDbDAO::orderFields()
{
	return QStringList() << "name";
}

QString TrainingDbDAO::tableName()
{
	return "Training";
}
