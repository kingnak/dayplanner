#include "dbautoiddaobase.h"
#include <QtSql>
#include "database.h"

DbAutoIdDAOBase::DbAutoIdDAOBase(DataBase *db, qint32 id, DAOBase::State s /* = DAOBase::New */)
    : DbDAOBase(db, s),
      m_id(id)
{

}

qint32 DbAutoIdDAOBase::id() const
{
    return m_id;
}

bool DbAutoIdDAOBase::doInsert()
{
    if (DbDAOBase::doInsert()) {
        QSqlQuery q = m_db->executeQuery("SELECT last_insert_rowid()");
        if (q.next()) {
            m_id = q.value(0).toInt();
            return true;
        } else {
            Q_ASSERT(false);
            return false;
        }
    }
    return false;
}

QStringList DbAutoIdDAOBase::keyFields()
{
    return QStringList() << "id";
}

QString DbAutoIdDAOBase::keyData(const QString &field)
{
    Q_ASSERT(field == "id");
	Q_UNUSED(field);
    return QString::number(m_id);
}
