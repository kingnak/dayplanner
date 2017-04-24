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

	enum {
		InvalidId = -1
	};

    QSqlQuery executeQuery(const QString &query);
    QSqlRecord selectSingleRecord(const QString &query);
    QSqlRecord selectIotaRecord(const QString &query);

    bool executeNonQuery(const QString &query);

	bool fillDefaultIngredients();

private:
    QSqlRecord selectOneRecord(const QString &query, bool warnIfNone);

private:
    static void createConnection();
	static QString getDbFile();
	static bool doFillDefaultIngredients();
};

#endif // DATABASE_H
