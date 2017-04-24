#include "ingredientlistdbdao.h"

IngredientListDbDAO::IngredientListDbDAO(DataBase *db, qint32 id)
	: DbAutoIdDAOBase(db, id)
{

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
