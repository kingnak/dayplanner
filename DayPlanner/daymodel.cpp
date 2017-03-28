#include "daymodel.h"
#include <QDate>
#include <QVariant>
#include <QDebug>
#include <algorithm>
#include "daydata.h"
#include "dao/db/dbdaofacade.h"

DayModel::DayModel()
{
    m_facade = new DbDAOFacade;
}

DayModel::~DayModel()
{
    delete m_facade;
}

QObject *DayModel::dataForDate(const QDate &date)
{
#ifdef CACHE_MONTH_DATA
    const QString dateStr = date.toString("yyyy-MM-dd");
    const QString monthStr = date.toString("yyyy-MM");

    if (m_cache.contains(monthStr) && m_cache[monthStr].contains(dateStr)) {
        return m_cache[monthStr][dateStr];
    }

    QObject *d = loadDay(date);
    m_cache[monthStr][dateStr] = d;
    return d;
#else
    const QString dateStr = date.toString("yyyy-MM-dd");
    if (m_cache.contains(dateStr)) {
        return m_cache[dateStr];
    }

    QObject *d = loadDay(date);
    m_cache[dateStr] = d;
    return d;
#endif
}

QObject *DayModel::loadDay(const QDate &date)
{
    DayData *d = new DayData(date, m_facade, this);
    return d;
}

void DayModel::clearCache(QDate date)
{
#ifdef CACHE_MONTH_DATA
    QStringList validDates;
    for (qint16 i = -static_cast<qint16>(PRESERVED_MONTHS); i <= PRESERVED_MONTHS; ++i) {
        validDates << date.addMonths(i).toString("yyyy-MM");
    }

    QList<QString> keys = m_cache.keys();
    for (auto k : keys) {
        if (!validDates.contains(k)) {
            std::for_each(m_cache[k].begin(), m_cache[k].end(), [](auto i){i->deleteLater();});
            m_cache.remove(k);
        }
    }
#else
    Q_UNUSED(date)
    std::for_each(m_cache.begin(), m_cache.end(), [](auto i) {i->deleteLater();});
    m_cache.clear();
#endif
}

