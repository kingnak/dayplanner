#include "ingrecuniformmodel.h"
#include "recipetemplatelist.h"
#include "ingredientlist.h"

IngRecUniformModel::IngRecUniformModel(RecipeTemplateList *recTempl, IngredientList *ingr)
	: m_recTempl(recTempl),
	  m_ingr(ingr)
{
	connect(m_ingr, &IngredientList::modelAboutToBeReset, this, &IngRecUniformModel::beginResetModel);
	connect(m_ingr, &IngredientList::modelReset, this, &IngRecUniformModel::endResetModel);
	connect(m_recTempl, &RecipeTemplateList::modelAboutToBeReset, this, &IngRecUniformModel::beginResetModel);
	connect(m_recTempl, &RecipeTemplateList::modelReset, this, &IngRecUniformModel::endResetModel);
}

QVariant IngRecUniformModel::data(const QModelIndex &index, int role) const
{
	if (isRecipe(index)) {
		if (role == TypeRole) return Recipe;
		if (role == NameRole) return m_recTempl->data(m_recTempl->index(index.row()), RecipeTemplateList::NameRole);
		if (role == IdRole) return m_recTempl->data(m_recTempl->index(index.row()), RecipeTemplateList::IdRole);
		if (role == IconUrlRole) return "qrc:///icons/recipe";
	}
	if (isIngredient(index)) {
		if (role == TypeRole) return Ingredient;
		int off = m_recTempl->rowCount(QModelIndex());
		if (role == NameRole) return m_ingr->data(m_ingr->index(index.row() - off), IngredientList::NameRole);
		if (role == IdRole) return m_ingr->data(m_ingr->index(index.row() - off), IngredientList::IdRole);
		if (role == IconUrlRole) return "qrc:///icons/ingredient";
	}
	return QVariant();
}

int IngRecUniformModel::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return m_recTempl->rowCount(parent) + m_ingr->rowCount(parent);
}

QHash<int, QByteArray> IngRecUniformModel::roleNames() const
{
	QHash<int, QByteArray> ret;
	ret[IdRole] = "itemId";
	ret[NameRole] = "name";
	ret[TypeRole] = "objectType";
	ret[IconUrlRole] = "iconUrl";
	return ret;
}

bool IngRecUniformModel::isRecipe(const QModelIndex &idx) const
{
	if (!idx.isValid()) return false;
	if (idx.row() >= m_recTempl->rowCount(QModelIndex())) return false;
	return true;
}

bool IngRecUniformModel::isIngredient(const QModelIndex &idx) const
{
	if (!idx.isValid()) return false;
	if (idx.row() >= m_recTempl->rowCount(QModelIndex())) return true;
	return false;
}
