#include "workout.h"

Workout::Workout(QObject *parent)
	: QObject(parent),
	  m_workout(nullptr)
{
	Q_ASSERT(false);
}

Workout::Workout(WorkoutDAO *workout, QObject *parent)
	: QObject(parent),
	  m_workout(workout)
{
}

Workout::~Workout()
{
	delete m_workout;
}

bool Workout::erase()
{
	return m_workout->remove();
}

QString Workout::name() const
{
	return m_workout->name();
}

void Workout::setName(const QString &n)
{
	if (n != name()) {
		m_workout->setName(n);
		m_workout->setTrainingId(0);
		if (m_workout->save()) {
			emit nameChanged();
		}
	}
}

QString Workout::info() const
{
	return m_workout->info();
}

void Workout::setInfo(const QString &i)
{
	if (i != info()) {
		m_workout->setInfo(i);
		if (m_workout->save()) {
			emit infoChanged();
		}
	}
}
