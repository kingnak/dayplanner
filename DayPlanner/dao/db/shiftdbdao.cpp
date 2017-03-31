#include "shiftdbdao.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

ShiftDbDAO::ShiftDbDAO(QDate d, DataBase *db)
    : DbDAOBase(db),
      m_date(d)
{
	if (!load())
		setData("d", keyData("d"));
}

QDate ShiftDbDAO::date() const
{
    return m_date;
}

int ShiftDbDAO::shiftIndex() const
{
	return data<int>("shiftId");
}

void ShiftDbDAO::setShiftIndex(int idx)
{
	setData("shiftId", idx);
}

QStringList ShiftDbDAO::keyFields()
{
    return QStringList() << "d";
}

QString ShiftDbDAO::keyData(const QString &field)
{
    if (field == "d") {
        return m_date.toString("yyyy-MM-dd");
    }
    return QString::null;
}

QString ShiftDbDAO::tableName()
{
    return "Shift";
}
