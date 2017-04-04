#ifndef WORKOUTLIST_H
#define WORKOUTLIST_H

#include <QObject>
#include <QDate>
#include <QQmlListProperty>
#include "workout.h"

class DAOFacade;

class WorkoutList : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QQmlListProperty<Workout> items READ items NOTIFY itemsChanged)
	Q_PROPERTY(int count READ count NOTIFY itemsChanged)
	Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY itemsChanged)

public:
	explicit WorkoutList(QObject *parent = nullptr);
	~WorkoutList();

	static WorkoutList *loadForDate(QObject *parent, DAOFacade *facade, QDate d);

	QQmlListProperty<Workout> items();

	Q_INVOKABLE void createWorkout(const QString &name);
	Q_INVOKABLE void createWorkoutForTraining(qint32 trainingId);
	Q_INVOKABLE void removeWorkout(qint32 idx);

	bool isEmpty() const;
	int count() const;

signals:
	void itemsChanged();

private:
	static Workout *atFunc(QQmlListProperty<Workout> *p, int i);
	static int countFunc(QQmlListProperty<Workout> *p);

private:
	QList<Workout *> m_data;
	QDate m_date;
	DAOFacade *m_facade;
};

#endif // WORKOUTLIST_H
