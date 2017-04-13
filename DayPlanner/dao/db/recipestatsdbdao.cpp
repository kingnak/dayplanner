#include "recipestatsdbdao.h"
#include <QVariant>

RecipeStatsDbDAO::RecipeStatsDbDAO(const QSqlRecord &rec)
	: m_record(rec)
{

}

qreal RecipeStatsDbDAO::getData(const QString &field) const
{
	return qvariant_cast<qreal>(m_record.value(field));
}
