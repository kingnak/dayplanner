#ifndef IMPORTEXPORTHELPER_H
#define IMPORTEXPORTHELPER_H

#include <QtGlobal>
#include <QList>

class Recipe;
class RecipeDAO;
class IngredientListItemDAO;

class ImportExportHelper
{
private:
	ImportExportHelper();
	Q_DISABLE_COPY(ImportExportHelper)

public:
	struct Header {
		QString name;
		qint32 servings = 0;
		bool isOverridden = false;
		qreal fat = 0.,
			protein = 0.,
			carbs = 0.,
			calories = 0.;
	};

	struct Item {
		QString name;
		qint32 quantity = 0;
		qreal fat = 0.,
			protein = 0.,
			carbs = 0.,
			calories = 0.;
	};

	static bool canImport(QString s);
	static bool importData(QString data, Header &header, QList<Item> &items);
	static QString exportData(const Header &header, const QList<Item> &items);
};

#endif // IMPORTEXPORTHELPER_H
