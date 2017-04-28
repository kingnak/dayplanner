#ifndef QMLUTILS_H
#define QMLUTILS_H

#include <QObject>
#include <QLocale>

class QmlUtils : public QObject
{
	Q_OBJECT
public:
	explicit QmlUtils();

	Q_INVOKABLE QString formatDouble(qreal n);
	Q_INVOKABLE qreal parseNumber(QString n);

	Q_INVOKABLE QString formatInt(qint32 n);
	Q_INVOKABLE qint32 parseInt(const QString &n);


private:
	QLocale m_locale;
};

#endif // QMLUTILS_H
