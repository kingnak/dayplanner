#ifndef INGREDIENTLISTDAO_H
#define INGREDIENTLISTDAO_H

#include "daobase.h"
#include <QtGlobal>

class IngredientListDAO : public virtual DAOBase
{
public:
	virtual qint32 id() const = 0;
};

#endif // INGREDIENTLISTDAO_H
