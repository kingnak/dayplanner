#ifndef DAYMODEL_H
#define DAYMODEL_H

#include <QObject>
#include <QMap>
#include <QDate>
#include <QString>

class DAOFacade;

class DayModel : public QObject
{
    Q_OBJECT
public:
    explicit DayModel();
    ~DayModel();

    Q_INVOKABLE QObject *dataForDate(const QDate &date);
    Q_INVOKABLE void clearCache(QDate date);

private:
    QObject *loadDay(const QDate &date);

private:
#ifdef CACHE_MONTH_DATA
    static const quint8 PRESERVED_MONTHS = 1;
    QMap<QString, QMap<QString, QObject*> > m_cache;
#else
    QMap<QString, QObject*> m_cache;
#endif

    DAOFacade *m_facade;
};

#endif // DAYMODEL_H
