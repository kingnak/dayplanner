#include "dbdaofacade.h"
#include "database.h"
#include "shiftdbdao.h"
#include "mealdbdao.h"
#include "recipedbdao.h"
#include "trainingdbdao.h"
#include "workoutdbdao.h"
#include <QtSql>

ShiftDAO *DbDAOFacade::loadShift(QDate d)
{
	return new ShiftDbDAO(d, &DataBase::instance());
}

QStringList DbDAOFacade::loadAllShifts()
{
	QString query = "SELECT name FROM ShiftList ORDER BY id ASC";
	QSqlQuery q = DataBase::instance().executeQuery(query);

	QStringList r;
	while (q.next()) {
		r << q.record().value("name").toString();
	}
	return r;
}

QList<MealDAO *> DbDAOFacade::loadMeals(QDate d, qint32 type)
{
    QString query = QString("SELECT id FROM Meal WHERE date = '%1' AND type = %2 ORDER BY sort")
            .arg(d.toString("yyyy-MM-dd"))
            .arg(type);

    QSqlQuery q = DataBase::instance().executeQuery(query);

    QList<MealDAO *> ret;
    while (q.next()) {
        MealDAO *m = new MealDbDAO(q.record().value(0).toInt(), &DataBase::instance());
        ret << m;
    }

    return ret;
}

MealDAO *DbDAOFacade::createMeal(QDate d, qint32 type)
{
    MealDbDAO *m = new MealDbDAO(-1, &DataBase::instance());
    m->setDate(d);
    m->setType(type);
    m->setFactor(1);

    QString query = QString("SELECT COUNT(*) FROM Meal WHERE date = '%1' AND type = %2")
            .arg(d.toString("yyyy-MM-dd"))
            .arg(type);

    QSqlQuery q = DataBase::instance().executeQuery(query);
    if (q.next()) {
        m->setSort(q.record().value(0).toInt() + 1);
    } else {
        m->setSort(1);
    }

    return m;
}

RecipeDAO *DbDAOFacade::loadRecipe(qint32 recipeId)
{
    return new RecipeDbDAO(recipeId, &DataBase::instance());
}

QList<RecipeDAO *> DbDAOFacade::loadRecipes()
{
    QString query = QString("SELECT * FROM Recipe ORDER BY name ASC");

    QSqlQuery q = DataBase::instance().executeQuery(query);

    QList<RecipeDAO *> ret;
    while (q.next()) {
        RecipeDAO *r = new RecipeDbDAO(q.record().value(0).toInt(), &DataBase::instance());
        ret << r;
    }

	return ret;
}

TrainingDAO *DbDAOFacade::loadTraining(qint32 trainingId)
{
	return new TrainingDbDAO(trainingId, &DataBase::instance());
}

QList<TrainingDAO *> DbDAOFacade::loadTrainings()
{
	QString query = QString("SELECT * FROM Training ORDER BY name ASC");

	QSqlQuery q = DataBase::instance().executeQuery(query);

	QList<TrainingDAO *> ret;
	while (q.next()) {
		TrainingDAO *r = new TrainingDbDAO(q.record().value(0).toInt(), &DataBase::instance());
		ret << r;
	}

	return ret;
}

QList<WorkoutDAO *> DbDAOFacade::loadWorkouts(QDate d)
{
	QString query = QString("SELECT id FROM Workout WHERE date = '%1' ORDER BY sort")
			.arg(d.toString("yyyy-MM-dd"));

	QSqlQuery q = DataBase::instance().executeQuery(query);

	QList<WorkoutDAO *> ret;
	while (q.next()) {
		WorkoutDAO *w = new WorkoutDbDAO(q.record().value(0).toInt(), &DataBase::instance());
		ret << w;
	}

	return ret;
}

WorkoutDAO *DbDAOFacade::createWorkout(QDate d)
{
	WorkoutDbDAO *w = new WorkoutDbDAO(-1, &DataBase::instance());
	w->setDate(d);

	QString query = QString("SELECT COUNT(*) FROM Workout WHERE date = '%1'")
			.arg(d.toString("yyyy-MM-dd"));

	QSqlQuery q = DataBase::instance().executeQuery(query);
	if (q.next()) {
		w->setSort(q.record().value(0).toInt());
	} else {
		w->setSort(1);
	}

	return w;
}
