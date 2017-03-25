#include "dbdaobase.h"
#include "database.h"
#include <QtSql>

#ifndef NDEBUG
#define BREAK_MSG(w,m) Q_ASSERT_X(false, w, m)
#else
#define BREAK_MSG(w,m) qFatal(w ": " m)
#endif

#define VERIFY(x, where, msg) do {\
    if (!(x)) {\
        BREAK_MSG(where, msg);\
    }\
    } while(false)

DbDAOBase::DbDAOBase(DataBase *db, State s)
    : DAOBase(s),
      m_db(db)
{

}

QString DbDAOBase::escapeTable(const QString &table)
{
    return "\"" + table + "\"";
}

QString DbDAOBase::escapeField(const QString &field)
{
    return escapeTable(field);
}

QString DbDAOBase::escapeValue(QString value)
{
    return "'" + value.replace("'", "''") + "'";
}

bool DbDAOBase::doReset()
{
    m_record = QSqlRecord();
    return true;
}

bool DbDAOBase::doLoad()
{
    m_record = m_db->selectSingleRecord(loadQuery());
    return !m_record.isEmpty();
}

bool DbDAOBase::doInsert()
{
    Q_ASSERT(m_state == New);
    bool ok = m_db->executeNonQuery(insertQuery());
    if (ok && isAutoId()) {
        QSqlQuery q = m_db->executeQuery("SELECT last_insert_rowid()");
        if (q.next()) {
            updateIdValue(q.value(0).toInt());
        } else {
            Q_ASSERT(false);
            return false;
        }
    }
    return ok;
}

bool DbDAOBase::doUpdate()
{
    Q_ASSERT(m_state == Existing);
    return m_db->executeNonQuery(updateQuery());
}

bool DbDAOBase::doRemove()
{
    Q_ASSERT(m_state == Existing);
    if (m_db->executeNonQuery(deleteQuery())) {
        doReset();
        return true;
    }
    return false;
}

QString DbDAOBase::loadQuery()
{
    QString q = QString("SELECT * FROM %1").arg(escapeTable(tableName()));
    q += keyCondition();
    QStringList ord = orderFields();
    if (!ord.isEmpty()) {
        q += " ORDER BY " + ord.join(", ");
    }

    return q;
}

QString DbDAOBase::insertQuery()
{
    QStringList fields, values;

    for (int i = 0; i < m_record.count(); ++i) {
        fields << escapeField(m_record.fieldName(i));
        values << escapeValue(m_record.value(i).toString());
    }

    QString q = QString("INSERT INTO %1 (%2) VALUES (%3)").arg(
                escapeTable(tableName()),
                fields.join(","),
                values.join(",")
                );
    return q;
}

QString DbDAOBase::updateQuery()
{
    QString cond = keyCondition();
    VERIFY(!cond.isEmpty(), "DbDAOBase", "Condition for update must not be empty!");

    QString q = QString("UPDATE %1 SET ").arg(escapeTable(tableName()));
    QStringList updates;

    QStringList keys = keyFields();
    for (int i = 0; i < m_record.count(); ++i) {
        if (keys.contains(m_record.fieldName(i))) {
            continue;
        }
        updates << QString("%1 = %2").arg(
                       escapeField(m_record.fieldName(i)),
                       escapeValue(data<QString>(m_record.fieldName(i)))
                       );
    }

    if (updates.isEmpty()) {
        qWarning() << "No fields to update";
        return QString::null;
    }

    q += updates.join(", ");
    q += cond;
    return q;
}

QString DbDAOBase::deleteQuery()
{
    QString cond = keyCondition();
    VERIFY(!cond.isEmpty(), "DbDAOBase", "Condition for delete must not be empty!");

    QString q = QString("DELETE FROM %1").arg(escapeTable(tableName()));
    q += cond;

    return q;
}

qint32 DbDAOBase::idValue() const
{
    VERIFY(false, "DbDAOBase", "Must override idValue if using default queries with auto id");
    return -1;
}

void DbDAOBase::updateIdValue(qint32 id)
{
    VERIFY(false, "DbDAOBase", "Must override updateIdValue if using default queries with auto id");
    Q_UNUSED(id)
}

QStringList DbDAOBase::keyFields()
{
    if (isAutoId()) {
        return QStringList() << "id";
    }
    VERIFY(false, "DbDAOBase", "Must override keyFields if using default queries");
    return QStringList();
}

QString DbDAOBase::keyData(const QString &field)
{
    if (isAutoId()) {
        return QString::number(idValue());
    }
    return data<QString>(field);
}

QStringList DbDAOBase::orderFields()
{
    return QStringList();
}

QString DbDAOBase::tableName()
{
    VERIFY(false, "DbDAOBase", "Must override tableName if using default queries");
    return QString::null;
}

bool DbDAOBase::isAutoId() const
{
    return false;
}

QString DbDAOBase::keyCondition()
{
    QString q;
    QStringList cond;
    for (auto k : keyFields()) {
        cond << QString("%1 = %2").arg(escapeField(k), escapeValue(keyData(k)));
    }
    if (!cond.empty()) {
        q += " WHERE (" + cond.join(") AND (") + ") ";
    }
    return q;
}
