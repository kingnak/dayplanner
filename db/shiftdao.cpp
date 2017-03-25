#include "shiftdao.h"
#include "database.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

ShiftDAO::ShiftDAO(QDate d, DataBase *db)
    : DbDAOBase(db),
      m_date(d)
{
    load();
}

/*
void ShiftDAO::load()
{
    const QString dateStr = m_date.toString("yyyy-MM-dd");
    const QString queryStr = QString::fromLatin1("SELECT d, shift FROM Dienst WHERE '%1' = d").arg(dateStr);

    QSqlQuery query = m_db->executeQuery(queryStr);
    if (query.next()) {
        m_record = query.record();
    }
}
*/

int ShiftDAO::shiftIndex() const
{
    return data<int>("shift");
}

void ShiftDAO::setShiftIndex(int idx)
{
    setData("shift", idx);
}

QStringList ShiftDAO::keyFields()
{
    return QStringList() << "d";
}

QString ShiftDAO::keyData(const QString &field)
{
    if (field == "d") {
        return m_date.toString("yyyy-MM-dd");
    }
    return QString::null;
}

QString ShiftDAO::tableName()
{
    return "Shift";
}


