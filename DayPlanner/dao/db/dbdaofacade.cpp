#include "dbdaofacade.h"
#include "database.h"
#include "shiftdbdao.h"
#include "mealdbdao.h"
#include "ingredientdbdao.h"
#include "trainingdbdao.h"
#include "workoutdbdao.h"
#include "ingredientstatsdbdao.h"
#include "recipetemplatedbdao.h"
#include "ingredientlistitemdbdao.h"
#include "ingredientlistdbdao.h"
#include "recipedbdao.h"
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
	MealDbDAO *m = new MealDbDAO(DataBase::InvalidId, &DataBase::instance());
    m->setDate(d);
    m->setType(type);
	m->setQuantity(1);

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

IngredientDAO *DbDAOFacade::loadIngredient(qint32 ingredientId)
{
    return new IngredientDbDAO(ingredientId, &DataBase::instance());
}

QList<IngredientDAO *> DbDAOFacade::loadIngredients()
{
    QString query = QString("SELECT * FROM Ingredient ORDER BY name ASC");

    QSqlQuery q = DataBase::instance().executeQuery(query);

    QList<IngredientDAO *> ret;
    while (q.next()) {
        IngredientDAO *r = new IngredientDbDAO(q.record().value(0).toInt(), &DataBase::instance());
        ret << r;
    }

	return ret;
}

IngredientDAO *DbDAOFacade::createIngredient(const QString &name)
{
	if (QScopedPointer<IngredientDAO>(loadIngredientByName(name)).data()) {
		return nullptr;
	}

	IngredientDAO *r = new IngredientDbDAO(DataBase::InvalidId, &DataBase::instance());
	r->setName(name);
	return r;
}

IngredientDAO *DbDAOFacade::loadIngredientByName(const QString &name)
{
	QSqlQuery query;
	query.prepare("SELECT * FROM Ingredient WHERE NAME LIKE ?");
	query.bindValue(0, name);
	query.exec();
	if (query.next()) {
		return new IngredientDbDAO(query.record().value(0).toInt(), &DataBase::instance());
	}

	return nullptr;
}

IngredientStatsDAO *DbDAOFacade::loadIngredientStats()
{
	QStringList l;
	for ( QString f : { "Fat", "Carbs", "Protein", "Calories" } ) {
		l << QString("MIN(%1) AS min%2, MAX(%1) AS max%2").arg(f.toLower(), f);
	}
	QString query = "SELECT " + l.join(", ") + " FROM Ingredient";
	QSqlQuery q = DataBase::instance().executeQuery(query);
	q.next();
	return new IngredientStatsDbDAO(q.record());
}

bool DbDAOFacade::removeIngredient(qint32 ingredientId)
{
	QString query = QString("UPDATE Meal SET IngredientId = 0 WHERE IngredientId = %1").arg(ingredientId);
	DataBase::instance().executeNonQuery(query);
	query = QString("DELETE FROM Ingredient WHERE id = %1").arg(ingredientId);
	return DataBase::instance().executeNonQuery(query);
}

QList<RecipeTemplateDAO *> DbDAOFacade::loadRecipeTemplates()
{
	QString query = QString("SELECT * FROM RecipeTemplate ORDER BY name ASC");

	QSqlQuery q = DataBase::instance().executeQuery(query);

	QList<RecipeTemplateDAO *> ret;
	while (q.next()) {
		RecipeTemplateDAO *r = new RecipeTemplateDbDAO(q.record().value(0).toInt(), &DataBase::instance());
		ret << r;
	}

	return ret;
}

IngredientListDAO *DbDAOFacade::createIngredientList()
{
	IngredientListDbDAO *ret = new IngredientListDbDAO(&DataBase::instance(), -1);
	ret->save();
	return ret;
}

RecipeDAO *DbDAOFacade::createRecipe()
{
	RecipeDAO *ret = new RecipeDbDAO(-1, &DataBase::instance());
	IngredientListDAO *lst = createIngredientList();
	ret->setIngredientListId(lst->id());
	delete lst;
	return ret;
}

QList<IngredientListItemDAO *> DbDAOFacade::loadIngredientListItems(qint32 listId)
{
	QString query = QString("SELECT * FROM IngredientListItem WHERE ingredientListId = %1 ORDER BY sort ASC").arg(listId);

	QSqlQuery q = DataBase::instance().executeQuery(query);

	QList<IngredientListItemDAO *> ret;
	while (q.next()) {
		IngredientListItemDAO *r = new IngredientListItemDbDAO(q.record().value(0).toInt(), &DataBase::instance());
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
	WorkoutDbDAO *w = new WorkoutDbDAO(DataBase::InvalidId, &DataBase::instance());
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
