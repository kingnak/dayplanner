#ifndef INGREDIENTLISTITEMDBDAO_H
#define INGREDIENTLISTITEMDBDAO_H

#include "../ingredientlistitemdao.h"
#include "dbautoiddaobase.h"

class IngredientListItemDbDAO : public IngredientListItemDAO, private DbAutoIdDAOBase
{
public:
	IngredientListItemDbDAO(qint32 id, DataBase *db);

	qint32 id() const;

	QString name() const;
	void setName(const QString &name);

	qint32 quantity() const;
	void setQuantity(qint32 q);

	qreal fat() const;
	void setFat(qreal f);

	qreal protein() const;
	void setProtein(qreal p);

	qreal carbs() const;
	void setCarbs(qreal c);

	qreal calories() const;
	void setCalories(qreal c);

	qint32 ingredientId() const;
	void setIngredientId(qint32 id);

	qint32 listId() const;
	void setListId(qint32 id);

	qint32 sort() const;
	void setSort(qint32 sort);

protected:
	virtual QStringList orderFields();
	virtual QString tableName();
};

#endif // INGREDIENTLISTITEMDBDAO_H
