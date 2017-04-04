#include "workoutdbdao.h"

WorkoutDbDAO::WorkoutDbDAO(qint32 id, DataBase *db)
	: DbAutoIdDAOBase(db, id)
{
	load();
}

QString WorkoutDbDAO::name() const
{
	return data<QString>("name");
}

void WorkoutDbDAO::setName(const QString &name)
{
	setData("name", name);
}

QString WorkoutDbDAO::info() const
{
	return data<QString>("info");
}

void WorkoutDbDAO::setInfo(const QString &info)
{
	setData("info", info);
}

QDate WorkoutDbDAO::date() const
{
	return data<QDate>("date");
}

void WorkoutDbDAO::setDate(QDate d)
{
	setData("date", d);
}

qint32 WorkoutDbDAO::trainingId() const
{
	return data<qint32>("trainingId");
}

void WorkoutDbDAO::setTrainingId(qint32 id)
{
	setData("trainingId", id);
}

qint32 WorkoutDbDAO::sort() const
{
	return data<qint32>("sort");
}

void WorkoutDbDAO::setSort(qint32 sort)
{
	setData("sort", sort);
}

QStringList WorkoutDbDAO::orderFields()
{
	return QStringList() << "sort";
}

QString WorkoutDbDAO::tableName()
{
	return "Workout";
}
