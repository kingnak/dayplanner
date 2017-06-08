#include "qmlutils.h"
#include "nutritionmath.h"

QmlUtils::QmlUtils()
	: m_locale(QLocale())
{

}

QString QmlUtils::formatDouble(qreal n)
{
	QString ret = m_locale.toString(n, 'f', 1);
	int pos = ret.indexOf(m_locale.decimalPoint());
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
	qreal q = m_locale.toDouble(n, &ok);
	if (!ok) {
		// Try removing group separator
		n.remove(m_locale.groupSeparator());
		q = m_locale.toDouble(n, &ok);
	}
	return q;
}

QString QmlUtils::formatInt(qint32 n)
{
	return m_locale.toString(n);
}

qint32 QmlUtils::parseInt(const QString &n)
{
	return m_locale.toInt(n);
}

qreal QmlUtils::scaldemanRatio(qreal fat, qreal carbs, qreal protein)
{
	return NutritionMath::scaldemanRatio(fat, carbs, protein);
}
