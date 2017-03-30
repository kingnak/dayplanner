#include "qmlutils.h"
#include <QLocale>

QmlUtils::QmlUtils()
{

}

QString QmlUtils::formatNumber(qreal n)
{
	QLocale l;
	QString ret = l.toString(n, 'f', 1);
	int pos = ret.indexOf(l.decimalPoint());
	if (pos >= 0) {
		if (ret.mid(pos+1) == "0") {
			ret = ret.left(pos);
		}
	}
	return ret;
}

qreal QmlUtils::parseNumber(QString n)
{
	bool ok;
	QLocale l;
	qreal q = l.toDouble(n, &ok);
	if (!ok) {
		// Try removing group separator
		n.remove(l.groupSeparator());
		q = l.toDouble(n, &ok);
	}
	return q;
}
