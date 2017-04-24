#ifndef INGREDIENTITEMLIST_H
#define INGREDIENTITEMLIST_H

#include <QObject>
#include <QQmlListProperty>
#include "ingredientlistitem.h"

class DAOFacade;
class IngredientDAO;

class IngredientItemList : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QQmlListProperty<IngredientListItem> items READ items NOTIFY itemsChanged)
	Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY itemsChanged)

public:
	explicit IngredientItemList(QObject *parent = 0);
	~IngredientItemList();

	static IngredientItemList *loadList(QObject *parent, DAOFacade *facade, qint32 id);

	QQmlListProperty<IngredientListItem> items();
	bool isEmpty() const;

signals:
	void itemsChanged();

private:
	static IngredientListItem *atFunc(QQmlListProperty<IngredientListItem> *p, int i);
	static int countFunc(QQmlListProperty<IngredientListItem> *p);

private:
	qint32 m_id;
	QList<IngredientListItem *> m_data;
	DAOFacade *m_facade;
};

#endif // INGREDIENTITEMLIST_H
