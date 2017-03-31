 #ifndef DAYDATA_H
#define DAYDATA_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QList>

class ShiftDAO;
class MealList;
class DAOFacade;

class DayData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDate date READ date NOTIFY neverNotified)
    Q_PROPERTY(int shiftIndex READ shiftIndex WRITE setShiftIndex NOTIFY shiftIndexChanged)
    Q_PROPERTY(MealList *breakfast READ breakfast NOTIFY neverNotified)
	Q_PROPERTY(MealList *lunch READ lunch NOTIFY neverNotified)
	Q_PROPERTY(MealList *dinner READ dinner NOTIFY neverNotified)
	Q_PROPERTY(MealList *snack READ snack NOTIFY neverNotified)

	Q_PROPERTY(qreal sumFat READ sumFat NOTIFY sumsChanged)
	Q_PROPERTY(qreal sumProtein READ sumProtein NOTIFY sumsChanged)
	Q_PROPERTY(qreal sumCarbs READ sumCarbs NOTIFY sumsChanged)
	Q_PROPERTY(qreal sumCalories READ sumCalories NOTIFY sumsChanged)

public:
    explicit DayData(const QDate &d, DAOFacade *facade, QObject *parent = 0);
    ~DayData();

    QDate date() const { return m_date; }

    int shiftIndex() const;
    void setShiftIndex(int i);

    MealList *breakfast() const;
	MealList *lunch() const;
	MealList *dinner() const;
	MealList *snack() const;

	qreal sumFat() const;
	qreal sumProtein() const;
	qreal sumCarbs() const;
	qreal sumCalories() const;

signals:
    void shiftIndexChanged(int idx);
	void sumsChanged();
    void neverNotified() /* Should never be used */;

private:
    QDate m_date;
    ShiftDAO *m_shift;
	QList<MealList *> m_meals;
};

#endif // DAYDATA_H
