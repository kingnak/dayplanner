#ifndef RECIPETEMPLATELIST_H
#define RECIPETEMPLATELIST_H

#include <QAbstractListModel>
#include <QHash>
#include <QList>

class RecipeTemplateDAO;

class RecipeTemplateList : public QAbstractListModel
{
	Q_OBJECT
public:
	RecipeTemplateList();
	~RecipeTemplateList();

	QVariant data(const QModelIndex &index, int role) const;
	int rowCount(const QModelIndex &parent) const;

	QHash<int, QByteArray> roleNames() const;
	enum {
		IdRole = Qt::UserRole + 1,
		NameRole,
		FatRole,
		ProteinRole,
		CarbsRole,
		CaloriesRole,
		ReferenceServingRole,
		DefaultServingRole,
		UrlRole,
		NoteRole,
		//IngredientListIdRole
	};

private:
	void load();

private:
	QList<RecipeTemplateDAO*> m_data;
};

#endif // RECIPETEMPLATELIST_H
