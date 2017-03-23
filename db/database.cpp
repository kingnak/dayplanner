#include "database.h"
#include <QtSql>
#include <QDate>
#include <QDebug>

DataBase::DataBase()
{
    createConnection();
}

DataBase &DataBase::instance()
{
    static DataBase inst_;
    return inst_;
}

QSqlQuery DataBase::executeQuery(const QString &query)
{
    QSqlQuery q;
    if (!q.exec(query)) {
        qWarning() << q.lastError().text() << " for query: " << query;
    }

    return q;
}

QSqlRecord DataBase::selectSingleRecord(const QString &query)
{
    return selectOneRecord(query, false);
}

QSqlRecord DataBase::selectIotaRecord(const QString &query)
{
    return selectOneRecord(query, true);
}

bool DataBase::executeNonQuery(const QString &query)
{
    QSqlQuery q;
    return q.exec(query);
}

QSqlRecord DataBase::selectOneRecord(const QString &query, bool warnIfNone)
{
    QSqlQuery q = executeQuery(query);
    if (q.next()) {
        QSqlRecord r = q.record();
        if (q.next()) {
            qWarning() << "Query has more than 1 result: " << query;
        }
        return r;
    } else if (warnIfNone) {
        qWarning() << "Query had no result: " << query;
    }

    return QSqlRecord();
}

void DataBase::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        qFatal("Cannot opoen database");
        return;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE Dienst (d DATE, shift INT)");
    for (int i = 0; i < 70; ++i) {
        QString q = QString("INSERT INTO Dienst VALUES('%1', %2)").arg(QDate::currentDate().addDays(i-35).toString("yyyy-MM-dd")).arg(i%6+1);
        bool b = query.exec(q);
        if (!b) {
            qWarning() << query.lastError().text();
        }
    }
}
