#include "ingredientitemlist.h"
#include "dao/dao.h"

IngredientItemList::IngredientItemList(QObject *parent)
	: QObject(parent),
	  m_id(0)
{

}

IngredientItemList::~IngredientItemList()
{
}

IngredientItemList *IngredientItemList::loadList(QObject *parent, DAOFacade *facade, qint32 id)
{
	IngredientItemList *ret = new IngredientItemList(parent);
	ret->m_id = id;

	QList<IngredientListItemDAO *> items = facade->loadIngredientListItems(id);
	for (auto i : items) {
		IngredientListItem *l = new IngredientListItem(i, ret);
		ret->m_data << l;
	}

	return ret;
}

QQmlListProperty<IngredientListItem> IngredientItemList::items()
{
	return QQmlListProperty<IngredientListItem> (this, nullptr, &IngredientItemList::countFunc, &IngredientItemList::atFunc);
}

bool IngredientItemList::isEmpty() const
{
	return m_data.isEmpty();
}

IngredientListItem *IngredientItemList::atFunc(QQmlListProperty<IngredientListItem> *p, int i)
{
	return static_cast<IngredientItemList *> (p->object)->m_data.at(i);
}

int IngredientItemList::countFunc(QQmlListProperty<IngredientListItem> *p)
{
	return static_cast<IngredientItemList *> (p->object)->m_data.count();
}
