#include "ingredientstatsdbdao.h"
#include <QVariant>

IngredientStatsDbDAO::IngredientStatsDbDAO(const QSqlRecord &rec)
	: m_record(rec)
{

}

qreal IngredientStatsDbDAO::getData(const QString &field) const
{
	return qvariant_cast<qreal>(m_record.value(field));
}
