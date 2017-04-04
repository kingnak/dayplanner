#include "traininglist.h"
#include "dao/dao.h"
#include "dao/trainingdao.h"

TrainingList::TrainingList()
{
	load();
}

TrainingList::~TrainingList()
{
	qDeleteAll(m_data);
}

QVariant TrainingList::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	switch (role) {
	case Qt::DisplayRole:
	case NameRole:
		return m_data[index.row()]->name();
	case IdRole:
		return m_data[index.row()]->id();
	default:
		return QVariant();
	}
}

int TrainingList::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return m_data.count();
}

QHash<int, QByteArray> TrainingList::roleNames() const
{
	QHash<int, QByteArray> ret;
	ret[IdRole] = "itemId";
	ret[NameRole] = "name";
	return ret;
}

void TrainingList::load()
{
	beginResetModel();
	QList<TrainingDAO*> oldList = m_data;
	m_data.clear();
	m_data = globalDAOFacade()->loadTrainings();
	endResetModel();

	qDeleteAll(oldList);
}
