#ifndef RECIPETEMPLATELIST_H
#define RECIPETEMPLATELIST_H

#include <QAbstractListModel>
#include <QHash>
#include <QList>

class RecipeTemplateDAO;
class RecipeDAO;
class Recipe;

class RecipeTemplateList : public QAbstractListModel
{
	Q_OBJECT
public:
	RecipeTemplateList();
	~RecipeTemplateList();

	QVariant data(const QModelIndex &index, int role) const;
	int rowCount(const QModelIndex &parent) const;

	Q_INVOKABLE qint32 instantiateTemplate(qint32 templateId);
	Q_INVOKABLE Recipe *loadTemplateById(qint32 templateId);
	Q_INVOKABLE bool removeTemplateById(qint32 templateId);
	Q_INVOKABLE Recipe *createTemplate();

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

class RecipeTemplateNotifier : public QObject
{
	Q_OBJECT

private:
	RecipeTemplateNotifier() : QObject(nullptr) {}

public:
	static RecipeTemplateNotifier *instance() {
		static RecipeTemplateNotifier inst_;
		return &inst_;
	}

public slots:
	void notifyChanges() {
		emit recipeTemplatesChanged();
	}

signals:
	void recipeTemplatesChanged();
};

#endif // RECIPETEMPLATELIST_H
