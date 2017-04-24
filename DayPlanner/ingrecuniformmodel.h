#ifndef INGRECUNIFORMMODEL_H
#define INGRECUNIFORMMODEL_H

#include <QAbstractListModel>

class RecipeTemplateList;
class IngredientList;

class IngRecUniformModel : public QAbstractListModel
{
	Q_OBJECT
public:
	IngRecUniformModel(RecipeTemplateList *recTempl, IngredientList *ingr);

	enum ObjectType {
		Ingredient,
		Recipe
	};
	Q_ENUM(ObjectType)

	QVariant data(const QModelIndex &index, int role) const;
	int rowCount(const QModelIndex &parent) const;

	QHash<int, QByteArray> roleNames() const;
	enum {
		IdRole = Qt::UserRole + 1,
		NameRole,
		TypeRole
	};

private:
	bool isRecipe(const QModelIndex &idx) const;
	bool isIngredient(const QModelIndex &idx) const;

private:
	RecipeTemplateList *m_recTempl;
	IngredientList *m_ingr;

};

#endif // INGRECUNIFORMMODEL_H
