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
    bool needInit = false;

//#define CLEANDB
#define LOCALFILE getDbFile()
#ifdef LOCALFILE
    QString s = LOCALFILE;
#ifdef CLEANDB
    QFile::remove(LOCALFILE);
#endif
    needInit = !QFile::exists(LOCALFILE);
    db.setDatabaseName(LOCALFILE);
#else
#ifndef CLEANDB
#define CLEANDB
#endif
    db.setDatabaseName(":memory:");
    needInit = true;
#endif

    if (!db.open()) {
        qFatal("Cannot opoen database");
        return;
    }

    if (needInit) {
		QSqlQuery query;
		bool ok = query.exec("CREATE TABLE ShiftList (id INT NOT NULL PRIMARY KEY, name TEXT)");
		ok = query.exec("INSERT INTO ShiftList (id, name) VALUES "
				   "(0, '0'), "
				   "(1, 'X'), "
				   "(2, 'A1'), "
				   "(3, 'A2'), "
				   "(4, 'A3'), "
				   "(5, 'Z1'), "
				   "(6, 'Z2'), "
				   "(7, 'N1'), "
				   "(8, 'N2')"
				   );

		ok = query.exec("CREATE TABLE Shift (d DATE NOT NULL PRIMARY KEY, shiftId INT)");
        /*
        for (int i = 0; i < 70; ++i) {
            QString q = QString("INSERT INTO Shift VALUES('%1', %2)").arg(QDate::currentDate().addDays(i-35).toString("yyyy-MM-dd")).arg(i%6+1);
            bool b = query.exec(q);
            if (!b) {
                qWarning() << query.lastError().text();
            }
        }
        */
		ok = query.exec("CREATE TABLE Meal (id INTEGER PRIMARY KEY, date DATE, type INT, name TEXT, factor REAL, fat REAL, protein REAL, carbs REAL, calories REAL, sort INT, recipeId INT NULL, recipeState INT DEFAULT 0)");
        /*
        for (int i = 0; i < 3; ++i) {
            QString s = QString("INSERT INTO Meal (date, type, name, factor, fat, sort) VALUES ('%1',1,'Essen %2',1,1,%3,%2)")
                    .arg(QDate::currentDate().toString("yyyy-MM-dd"))
                    .arg(i+1)
                    .arg(i*2+4);
            bool b = query.exec(s);
            if (!b) {
                qWarning() << query.lastError().text();
            }
        }
        */
		ok = query.exec("CREATE TABLE Recipe (id INTEGER PRIMARY KEY, name TEXT, quantity INT, fat REAL, protein REAL, carbs REAL, calories REAL, url TEXT NULL)");

        QString dataFile = QDir(qApp->arguments().value(1)).absoluteFilePath("data/data.csv");
        QFile fdata(dataFile);
        if (fdata.exists() && fdata.open(QIODevice::ReadOnly)) {
            QTextStream ts(&fdata);
            ts.setCodec("utf8");
            QString line;
            query.exec("BEGIN TRANSACTION");
            QSqlQuery ins;
            ins.prepare("INSERT INTO Recipe (name, quantity, fat, protein, carbs, calories) VALUES (?,?,?,?,?,?)");
            while (!(line = ts.readLine()).isEmpty()) {
                QStringList parts = line.split(";");
                ins.addBindValue(parts[0]);
                ins.addBindValue(parts[2].toInt() / 100);
                ins.addBindValue(parts[5].toDouble() / 100);
                ins.addBindValue(parts[4].toDouble() / 100);
                ins.addBindValue(parts[6].toDouble() / 100);
                ins.addBindValue(parts[3].toDouble() / 100);

                if (!ins.exec()) {
                    qWarning() << ins.executedQuery();
                    qWarning() << ins.lastError().text() << ins.lastError();
                }
            }
            query.exec("COMMIT");
        } else {
            qWarning().noquote() << dataFile << "cannot be opened";
        }

		ok = query.exec("CREATE TABLE Training (id INTEGER PRIMARY KEY, name TEXT)");
		ok = query.exec("INSERT INTO Training (name) VALUES "
				   "('Laufen'),"
				   "('Crossfit'),"
				   "('EMS'),"
				   "('Bauch'),"
				   "('Sonstiges')"
				   );

		ok = query.exec("CREATE TABLE Workout (id INTEGER PRIMARY KEY, date DATE, name TEXT, info TEXT, trainingId INT NULL, sort INT)");
	}
}

QString DataBase::getDbFile()
{
	QProcessEnvironment sysEnv = QProcessEnvironment::systemEnvironment();
	QDir base;
	if (sysEnv.contains("LOCALAPPDATA")) {
		// On windows XP, this doesn't exist... not supported
		base = QDir(sysEnv.value("LOCALAPPDATA"));
	} else {
		qWarning() << "Cannot determine configuration directory. Using guessed directory";
		base = QDir("C:\\ProgramData");
		if (!base.exists()) {
			// Try application dir... is probably write protected...
			base = qApp->applicationDirPath();
		}
	}

	if (!base.exists("dayplanner")) {
		base.mkpath("dayplanner");
	}
	if (!base.cd("dayplanner")) {
		qWarning() << "Cannot create" << base.absoluteFilePath("dayplanner");
	}

	return base.absoluteFilePath("dayplanner.db");
}
