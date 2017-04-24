#ifndef INGREDIENTLISTDBDAO_H
#define INGREDIENTLISTDBDAO_H

#include "../ingredientlistdao.h"
#include "dbautoiddaobase.h"

class IngredientListDbDAO : public IngredientListDAO, private DbAutoIdDAOBase
{
public:
	IngredientListDbDAO(DataBase *db, qint32 id);

	qint32 id() const;

	DAO_USE(DbAutoIdDAOBase)

protected:
	virtual QString tableName();
	virtual QString insertQuery();
};

#endif // INGREDIENTLISTDBDAO_H
