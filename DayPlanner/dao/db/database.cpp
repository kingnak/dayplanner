#include "database.h"
#include <QtSql>
#include <QDate>
#include <QDebug>

// Version = 0.3
#define DB_VERSION 0x0003

DataBase::DataBase()
{
    createConnection();
}

DataBase::DbStartupError DataBase::s_startError = DataBase::NoError;

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
	bool b = q.exec(query);
	if (!b) {
		qWarning() << "Error " << q.lastError().text() << " in query: " << query;
	}
	return b;
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
	s_startError = UnknownError;
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
		s_startError = CannotOpen;
        return;
    }

    if (needInit) {
		QSqlQuery query;
		bool ok = query.exec("CREATE TABLE ShiftList (id INT NOT NULL PRIMARY KEY, name TEXT)");
		ok &= query.exec("INSERT INTO ShiftList (id, name) VALUES "
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

		ok &= query.exec("CREATE TABLE Shift (d DATE NOT NULL PRIMARY KEY, shiftId INT)");
		ok &= query.exec("CREATE TABLE Meal (id INTEGER PRIMARY KEY, date DATE, type INT, name TEXT, quantity INT, fat REAL, protein REAL, carbs REAL, calories REAL, sort INT, ingredientId INT NULL, recipeId INT NULL)");
		ok &= query.exec("CREATE TABLE Ingredient (id INTEGER PRIMARY KEY, name TEXT, refQuantity INT, defaultQuantity INT, fat REAL, protein REAL, carbs REAL, calories REAL)");
		ok &= query.exec("CREATE TABLE RecipeTemplate (id INTEGER PRIMARY KEY, name TEXT, refServing INT, defaultServing INT, fat REAL, protein REAL, carbs REAl, calories REAL, url TEXT NULL, note TEXT NULL, ingredientListId INT DEFAULT 0, overridden INT DEFAULT 0)");
		ok &= query.exec("CREATE TABLE Recipe (id INTEGER PRIMARY KEY, name TEXT, refServing INT, defaultServing INT, fat REAL, protein REAL, carbs REAl, calories REAL, url TEXT NULL, note TEXT NULL, ingredientListId INT DEFAULT 0, overridden INT DEFAULT 0, templateId INT DEFAULT 0)");
		ok &= query.exec("CREATE TABLE IngredientList (id INTEGER PRIMARY KEY)");
		ok &= query.exec("CREATE TABLE IngredientListItem (id INTEGER PRIMARY KEY, ingredientListId INT, sort INT, name TEXT, quantity INT, fat REAL, protein REAL, carbs REAL, calories REAL, ingredientId INT)");

		doFillDefaultIngredients();

		ok &= query.exec("CREATE TABLE Training (id INTEGER PRIMARY KEY, name TEXT)");
		ok &= query.exec("INSERT INTO Training (name) VALUES "
				   "('Laufen'),"
				   "('Crossfit'),"
				   "('EMS'),"
				   "('Bauch'),"
				   "('Sonstiges')"
				   );

		ok &= query.exec("CREATE TABLE Workout (id INTEGER PRIMARY KEY, date DATE, name TEXT, info TEXT, trainingId INT NULL, sort INT)");
		ok &= query.exec("CREATE TABLE DbVersion (version INTEGER)");
		ok &= query.exec(QString("INSERT INTO DbVersion (version) VALUES (%1)").arg(DB_VERSION));

		if (!ok) {
			s_startError = InitError;
		} else {
			s_startError = NoError;
		}
	} else {
		QSqlQuery q("SELECT version FROM DbVersion");
		int dbVersion = 0;
		if (q.next()) {
			dbVersion = q.record().value(0).toInt();
		}

		if (dbVersion == DB_VERSION) {
			s_startError = NoError;
		} else if (dbVersion > DB_VERSION) {
			s_startError = TooNew;
		} else {
			s_startError = TooOld;
		}
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

bool DataBase::fillDefaultIngredients()
{
	return DataBase::doFillDefaultIngredients();
}

DataBase::DbStartupError DataBase::getStartupError() const
{
	return s_startError;
}

bool DataBase::doFillDefaultIngredients()
{
	QSqlQuery query;
	QString dataFile = ":/data/data.csv";
	QFile fdata(dataFile);
	if (fdata.exists() && fdata.open(QIODevice::ReadOnly)) {
		QTextStream ts(&fdata);
		ts.setCodec("utf8");
		QString line;
		query.exec("BEGIN TRANSACTION");
		QSqlQuery ins;
		ins.prepare("INSERT INTO Ingredient (name, refQuantity, defaultQuantity, fat, protein, carbs, calories) VALUES (?,?,?,?,?,?,?)");

		/// TEST
		//QSqlQuery insR;
		//insR.prepare("INSERT INTO RecipeTemplate (name, refServing, defaultServing, fat, protein, carbs, calories) VALUES (?,?,?,?,?,?,?)");



		QSqlQuery check;
		check.prepare("SELECT COUNT(*) FROM Ingredient WHERE name LIKE ?");
		while (!(line = ts.readLine()).isEmpty()) {
			QStringList parts = line.split(";");

			check.addBindValue(parts[0]);
			check.exec();
			if (check.next() && check.record().value(0).toInt() == 0) {

				ins.addBindValue(parts[0]);
				ins.addBindValue(parts[2].toInt() / 100);
				ins.addBindValue(parts[2].toInt() / 100);
				ins.addBindValue(parts[5].toDouble() / 100);
				ins.addBindValue(parts[4].toDouble() / 100);
				ins.addBindValue(parts[6].toDouble() / 100);
				ins.addBindValue(parts[3].toDouble() / 100);

				/// TEST
				/*
				insR.addBindValue(parts[0]);
				insR.addBindValue(1);
				insR.addBindValue(1);
				insR.addBindValue(parts[5].toDouble() / 100);
				insR.addBindValue(parts[4].toDouble() / 100);
				insR.addBindValue(parts[6].toDouble() / 100);
				insR.addBindValue(parts[3].toDouble() / 100);
				insR.exec();
				*/
				if (!ins.exec()) {
					qWarning() << ins.executedQuery();
					qWarning() << ins.lastError().text() << ins.lastError();
				}
			} else {
				qDebug() << parts[0] << "already in DB";
			}
		}
		query.exec("COMMIT");
		return true;
	} else {
		qWarning().noquote() << dataFile << "cannot be opened";
		return false;
	}
}
