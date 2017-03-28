#include "parser.h"

Parser::Parser(QObject *parent) : QObject(parent)
{

}

bool Parser::parseItem(const QString &item, QString data)
{
    QStringList d;

#define CHECK(c,i,e) if (c) return doEmitError(i,e)

    int pos = data.indexOf("<table ");
    CHECK(pos < 0, item, "No Table");

    pos = data.indexOf("<tr", pos);
    CHECK(pos < 0,item, "No tr");

    pos = data.indexOf("</tr", pos);
    CHECK(pos < 0, item, "No tr end");

    pos = data.indexOf("<tr", pos);
    CHECK(pos < 0, item, "No second tr");

    pos = data.indexOf(">", pos) + 1;
    data = data.mid(pos).trimmed();
    pos = data.indexOf("</tr");
    CHECK(pos < 0, item, "No second tr end");

    data = data.left(pos);

    QRegExp tdStart("<td[^>]*>");
    QRegExp tdEnd("</td\\s*>");

    data = data.split(tdStart).join("");
    d = data.split(tdEnd);

    CHECK(d.count() < 6, item, "Expected at least 6 columns, got" + d.count());

    QString itemData = d[0].trimmed();
    if (itemData != item.trimmed()) {
        emit error(item, "WARNING: Wrong item: " + d[0]);
    }

    QString qtStr = d[1];
    pos = qtStr.indexOf("<span");
    CHECK(pos<0, item, "No span in quantity");
    pos = qtStr.indexOf(">", pos);
    CHECK(pos<0, item, "No > after span in quantity");
    qtStr = qtStr.mid(pos+1);
    pos = qtStr.indexOf("</span");
    CHECK(pos<0, item, "No span end in quantity");
    qtStr = qtStr.left(pos);

    QString qt, kcal, prot, fat, carbs, sugar, ball, alc;
    CHECK(!extractNumber(qtStr.split(" ")[0], qt), item, "2nd column must be number");
    CHECK(!extractNumber(d[2].split("/")[0].trimmed(), kcal), item, "3rd column must be number");
    CHECK(!extractNumber(d[3], prot), item, "4th column must be number");
    CHECK(!extractNumber(d[4], fat), item, "5th column must be number");
    CHECK(!extractNumber(d[5], carbs), item, "6th column must be number");
    CHECK(!extractNumber(d.value(6), sugar), item, "7th column must be number");
    CHECK(!extractNumber(d.value(7), ball), item, "8th column must be number");
    CHECK(!extractNumber(d.value(8), alc), item, "9th column must be number");

    QStringList ret = QStringList()
            << itemData << qt << kcal << prot << fat << carbs << sugar << ball << alc;

    emit parsed(item, ret);
    return true;
#undef CHECK
}

void Parser::parseError(const QString &item, const QString &data)
{
    emit error(item, data);
}

bool Parser::extractNumber(QString v, QString &n)
{
    n = "0";
    v = v.trimmed();
    v = v.remove('.');
    bool ok;
    qint32 i = v.toInt(&ok, 10);
    if (!ok) return false;
    n = QString::number(i);
    return true;
}

bool Parser::doEmitError(const QString &item, const QString &err)
{
    emit error(item, err);
    return false;
}
