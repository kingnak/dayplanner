#include "importexporthelper.h"
#include "dao/recipedao.h"
#include <QTextStream>

bool ImportExportHelper::canImport(QString s)
{
	s = s.trimmed();
	if (s.isEmpty()) return false;

	QStringList lines = s.split('\n');
	if (lines.size() <= 1) return false;

	QString first = lines.takeAt(0);
	QStringList parts = first.split(';');
	if (parts.length() < 2) return false;

	bool ok;
	parts[1].toInt(&ok);
	if (!ok) return false;

	bool hasLine = false;
	for (QString s : lines) {
		s = s.trimmed();
		if (s.isEmpty()) continue;

		hasLine = true;

		QStringList parts = s.split(';');
		if (parts.length() < 2) return false;
		parts[1].toInt(&ok);
		if (!ok) return false;
	}

	return hasLine;
}

bool ImportExportHelper::importData(QString data, ImportExportHelper::Header &header, QList<ImportExportHelper::Item> &items)
{
	header = Header();
	items.clear();

	data = data.trimmed();

	// Header
	QStringList lines = data.split('\n');
	QString h = lines.takeAt(0);

	QStringList headerParts = h.split(';');
	if (headerParts.length() < 2) return false;

	header.name = headerParts[0];

	bool ok;
	header.servings = headerParts[1].toInt(&ok);
	if (!ok || header.servings < 1) return false;

	header.isOverridden = headerParts.length() > 2 ? headerParts[2].toInt(&ok) != 0 : false;
	if (!ok) return false;

	if (header.isOverridden) {
		header.fat = headerParts.value(3).toDouble();
		header.carbs = headerParts.value(4).toDouble();
		header.protein = headerParts.value(5).toDouble();
		header.calories = headerParts.value(6).toDouble();
	}

	// Items
	for (QString l : lines) {
		l = l.trimmed();
		if (l.isEmpty()) continue;

		QStringList parts = l.split(';');
		if (parts.length() < 2) return false;

		Item itm;
		itm.name = parts[0];
		itm.quantity = parts[1].toInt(&ok);
		if (!ok) return false;
		itm.fat = parts.value(2).toDouble();
		itm.carbs = parts.value(3).toDouble();
		itm.protein = parts.value(4).toDouble();
		itm.calories = parts.value(5).toDouble();

		items << itm;
	}

	return true;
}

QString ImportExportHelper::exportData(const ImportExportHelper::Header &header, const QList<ImportExportHelper::Item> &items)
{
	QString ret;
	{
		QTextStream s(&ret);
		s.setCodec("utf-8");
		s << header.name << ';' << header.servings;
		if (header.isOverridden) {
			s << ";1;"
			  << header.fat << ';'
			  << header.carbs << ';'
			  << header.protein << ';'
			  << header.calories << '\n';
		} else {
			s << ";0\n";
		}

		for (auto i : items) {
			s << i.name  << ';'
			  << i.quantity << ';'
			  << i.fat << ';'
			  << i.carbs << ';'
			  << i.protein << ';'
			  << i.calories << '\n';
		}
	}

	return ret;
}
