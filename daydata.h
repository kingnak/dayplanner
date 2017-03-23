 #ifndef DAYDATA_H
#define DAYDATA_H

#include <QObject>
#include <QString>
#include <QDate>

#include "db/dao.h"

class DayData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDate date READ date NOTIFY dateChanged)
    Q_PROPERTY(int shiftIndex READ shiftIndex WRITE setShiftIndex NOTIFY shiftIndexChanged)

public:
    explicit DayData(const QDate &d, DAOFacade *facade, QObject *parent = 0);

    QDate date() const { return m_date; }

    int shiftIndex() const;
    void setShiftIndex(int i);

signals:
    void shiftIndexChanged(int idx);
    void dateChanged(const QDate &d) /* Should never be used */;

private:
    QDate m_date;
    ShiftDAO m_shift;
};

#endif // DAYDATA_H
