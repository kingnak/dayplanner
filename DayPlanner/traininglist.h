#ifndef TRAININGLIST_H
#define TRAININGLIST_H

#include <QAbstractListModel>
#include <QList>
#include <QHash>

class TrainingDAO;

class TrainingList : public QAbstractListModel
{
public:
	TrainingList();
	~TrainingList();

	QVariant data(const QModelIndex &index, int role) const;
	int rowCount(const QModelIndex &parent) const;

	QHash<int, QByteArray> roleNames() const;
	enum {
		IdRole = Qt::UserRole + 1,
		NameRole
	};

private:
	void load();

private:
	QList<TrainingDAO*> m_data;
};

#endif // TRAININGLIST_H
