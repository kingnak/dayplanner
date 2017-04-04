#ifndef WORKOUT_H
#define WORKOUT_H

#include <QObject>
#include "dao/workoutdao.h"

class Workout : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(QString info READ info WRITE setInfo NOTIFY infoChanged)

public:
	explicit Workout(QObject *parent = 0);
	explicit Workout(WorkoutDAO *workout, QObject *parent = 0);
	~Workout();

	bool erase();

	QString name() const;
	void setName(const QString &n);

	QString info() const;
	void setInfo(const QString &i);

signals:
	void nameChanged();
	void infoChanged();

private:
	WorkoutDAO *m_workout;
};

#endif // WORKOUT_H
