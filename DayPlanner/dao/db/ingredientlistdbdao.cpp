#include "ingredientlistdbdao.h"

IngredientListDbDAO::IngredientListDbDAO(qint32 id, DataBase *db)
	: DbAutoIdDAOBase(db, id)
{
	load();
}

qint32 IngredientListDbDAO::id() const
{
	return DbAutoIdDAOBase::id();
}

QString IngredientListDbDAO::tableName()
{
	return "IngredientList";
}

QString IngredientListDbDAO::insertQuery()
{
	return "INSERT INTO " + escapeTable(tableName()) + " (id) VALUES (NULL)";
}
