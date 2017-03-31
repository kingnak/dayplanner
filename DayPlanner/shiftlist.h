#ifndef SHIFTLIST_H
#define SHIFTLIST_H

#include <QObject>

class ShiftList : public QObject
{
	Q_OBJECT
public:
	explicit ShiftList();

	Q_PROPERTY(QStringList shiftList READ shiftList NOTIFY shiftListChanged)

	QStringList shiftList();

signals:
	void shiftListChanged();

private:
	QStringList m_shifts;
};

#endif // SHIFTLIST_H
