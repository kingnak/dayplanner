#ifndef DATABASE_H
#define DATABASE_H

#include <QtGlobal>

class QSqlQuery;
class QSqlRecord;

class DataBase
{
private:
    DataBase();
    Q_DISABLE_COPY(DataBase)

public:
    static DataBase &instance();

    QSqlQuery executeQuery(const QString &query);
    QSqlRecord selectSingleRecord(const QString &query);
    QSqlRecord selectIotaRecord(const QString &query);

    bool executeNonQuery(const QString &query);

private:
    QSqlRecord selectOneRecord(const QString &query, bool warnIfNone);

private:
    static void createConnection();
};

#endif // DATABASE_H
