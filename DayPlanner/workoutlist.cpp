#include "workoutlist.h"
#include "dao/dao.h"
#include "dao/trainingdao.h"

WorkoutList::WorkoutList(QObject *parent)
	: QObject(parent)
{

}

WorkoutList::~WorkoutList()
{

}

WorkoutList *WorkoutList::loadForDate(QObject *parent, DAOFacade *facade, QDate d)
{
	WorkoutList *ret = new WorkoutList(parent);
	ret->m_date = d;
	ret->m_facade = facade;

	QList<WorkoutDAO *> workouts = facade->loadWorkouts(d);

	for (auto workout : workouts) {
		Workout *w = new Workout(workout, ret);
		ret->m_data << w;
	}

	return ret;
}

QQmlListProperty<Workout> WorkoutList::items()
{
	return QQmlListProperty<Workout> (this, nullptr, &WorkoutList::countFunc, &WorkoutList::atFunc);
}

void WorkoutList::createWorkout(const QString &name)
{
	WorkoutDAO *w = m_facade->createWorkout(m_date);
	if (!w) {
		return;
	}
	w->setName(name);
	if (w->save()) {
		Workout *wd = new Workout(w, this);
		m_data.append(wd);
		emit itemsChanged();
	} else {
		delete w;
	}
}

void WorkoutList::createWorkoutForTraining(qint32 trainingId)
{
	if (trainingId < 0) {
		return;
	}

	QScopedPointer<WorkoutDAO> w(m_facade->createWorkout(m_date));
	if (!w) {
		return;
	}

	QScopedPointer<TrainingDAO> t(m_facade->loadTraining(trainingId));
	if (!t) {
		return;
	}

	w->setName(t->name());
	w->setTrainingId(t->id());

	if (w->save()) {
		Workout *wd = new Workout(w.take(), this);
		m_data.append(wd);
		emit itemsChanged();
	}
}

void WorkoutList::removeWorkout(qint32 idx)
{
	if (idx < 0 || idx >= m_data.count()) {
		return;
	}

	Workout *w = m_data.takeAt(idx);
	w->erase();
	w->deleteLater();
	emit itemsChanged();
}

bool WorkoutList::isEmpty() const
{
	return m_data.isEmpty();
}

int WorkoutList::count() const
{
	return m_data.count();
}

Workout *WorkoutList::atFunc(QQmlListProperty<Workout> *p, int i)
{
	return static_cast<WorkoutList *> (p->object)->m_data.at(i);
}

int WorkoutList::countFunc(QQmlListProperty<Workout> *p)
{
	return static_cast<WorkoutList *> (p->object)->m_data.count();
}
