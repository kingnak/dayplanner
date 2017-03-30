#ifndef QMLUTILS_H
#define QMLUTILS_H

#include <QObject>

class QmlUtils : public QObject
{
	Q_OBJECT
public:
	explicit QmlUtils();

	Q_INVOKABLE QString formatNumber(qreal n);
	Q_INVOKABLE qreal parseNumber(QString n);

signals:

public slots:
};

#endif // QMLUTILS_H
