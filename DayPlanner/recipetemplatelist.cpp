#include "recipetemplatelist.h"
#include "dao/recipetemplatedao.h"
#include "dao/dao.h"

RecipeTemplateList::RecipeTemplateList()
{
	load();
}

RecipeTemplateList::~RecipeTemplateList()
{
	qDeleteAll(m_data);
}

QVariant RecipeTemplateList::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	switch (role) {
	case Qt::DisplayRole:
	case NameRole:
		return m_data[index.row()]->name();
	case IdRole:
		return m_data[index.row()]->id();
	case FatRole:
		return m_data[index.row()]->fat();
	case ProteinRole:
		return m_data[index.row()]->protein();
	case CarbsRole:
		return m_data[index.row()]->carbs();
	case CaloriesRole:
		return m_data[index.row()]->calories();
	case ReferenceServingRole:
		return m_data[index.row()]->referenceServing();
	case DefaultServingRole:
		return m_data[index.row()]->defaultServing();
	case UrlRole:
		return m_data[index.row()]->url();
	case NoteRole:
		return m_data[index.row()]->note();
	default:
		return QVariant();
	}
}

int RecipeTemplateList::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return m_data.count();
}

QHash<int, QByteArray> RecipeTemplateList::roleNames() const
{
	QHash<int, QByteArray> ret;
	ret[IdRole] = "itemId";
	ret[NameRole] = "name";
	ret[FatRole] = "fat";
	ret[ProteinRole] = "protein";
	ret[CarbsRole] = "carbs";
	ret[CaloriesRole] = "calories";
	ret[ReferenceServingRole] = "quantity";
	ret[DefaultServingRole] = "defaultQuantity";
	ret[UrlRole] = "url";
	ret[NoteRole] = "note";
	//ret[IngredientListIdRole] = "ingredientListId";
	return ret;
}

void RecipeTemplateList::load()
{
	beginResetModel();
	QList<RecipeTemplateDAO*> oldList = m_data;
	m_data.clear();
	m_data = globalDAOFacade()->loadRecipeTemplates();
	endResetModel();

	qDeleteAll(oldList);
}
