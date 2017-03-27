 #ifndef DAYDATA_H
#define DAYDATA_H

#include <QObject>
#include <QString>
#include <QDate>

class ShiftDAO;
class MealList;
class DAOFacade;

class DayData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDate date READ date NOTIFY neverNotified)
    Q_PROPERTY(int shiftIndex READ shiftIndex WRITE setShiftIndex NOTIFY shiftIndexChanged)
    Q_PROPERTY(MealList *breakfast READ breakfast NOTIFY neverNotified)

public:
    explicit DayData(const QDate &d, DAOFacade *facade, QObject *parent = 0);
    ~DayData();

    QDate date() const { return m_date; }

    int shiftIndex() const;
    void setShiftIndex(int i);

    MealList *breakfast() const;

signals:
    void shiftIndexChanged(int idx);
    void neverNotified() /* Should never be used */;

private:
    QDate m_date;
    ShiftDAO *m_shift;
    MealList *m_breakfast;
};

#endif // DAYDATA_H
