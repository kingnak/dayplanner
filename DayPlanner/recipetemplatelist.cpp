#include "recipetemplatelist.h"
#include "dao/recipetemplatedao.h"
#include "dao/dao.h"
#include "dao/recipedao.h"
#include "ingredientitemlist.h"
#include "recipe.h"

RecipeTemplateList::RecipeTemplateList()
{
	connect(RecipeTemplateNotifier::instance(), &RecipeTemplateNotifier::recipeTemplatesChanged, this, &RecipeTemplateList::load);
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

qint32 RecipeTemplateList::instantiateTemplate(qint32 templateId)
{
	QScopedPointer<RecipeTemplateDAO> tmpl(globalDAOFacade()->loadRecipeTemplate(templateId));
	if (tmpl->state() != DAOBase::Existing) {
		return DAOBase::NoItemIndex;
	}

	QScopedPointer<IngredientItemList> ingOrig(IngredientItemList::loadList(nullptr, globalDAOFacade(), tmpl->ingredientListId()));
	QScopedPointer<RecipeDAO> rec(globalDAOFacade()->createRecipe());
	QScopedPointer<IngredientItemList> ingCopy(IngredientItemList::loadList(nullptr, globalDAOFacade(), rec->ingredientListId()));
	ingOrig->copyInto(ingCopy.data());

	rec->setName(tmpl->name());
	rec->setNote(tmpl->note());
	rec->setUrl(tmpl->url());
	rec->setFat(tmpl->fat());
	rec->setProtein(tmpl->protein());
	rec->setCarbs(tmpl->carbs());
	rec->setCalories(tmpl->calories());
	rec->setDefaultServing(tmpl->defaultServing());
	rec->setReferenceServing(tmpl->referenceServing());

	rec->setTemplateId(tmpl->id());
	if (rec->save()) {
		return rec->id();
	}
	return DAOBase::NoItemIndex;
}

Recipe *RecipeTemplateList::loadTemplateById(qint32 templateId)
{
	RecipeTemplateDAO *r = globalDAOFacade()->loadRecipeTemplate(templateId);
	if (r && r->state() == DAOBase::Existing) {
		return new Recipe(r, this);
	}
	return nullptr;
}

bool RecipeTemplateList::removeTemplateById(qint32 templateId)
{
	if (globalDAOFacade()->removeRecipeTemplate(templateId)) {
		RecipeTemplateNotifier::instance()->notifyChanges();
		return true;
	}
	return false;
}

Recipe *RecipeTemplateList::createTemplate()
{
	return new Recipe(globalDAOFacade()->createRecipeTemplate(), this);
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
