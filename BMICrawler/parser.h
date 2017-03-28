#ifndef PARSER_H
#define PARSER_H

#include <QObject>

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);

signals:
    void parsed(const QString &item, const QStringList &data);
    void error(const QString &item, const QString &err);

public slots:
    bool parseItem(const QString &item, QString data);
    void parseError(const QString &item, const QString &data);

private:
    static bool extractNumber(QString v, QString &n);
    bool doEmitError(const QString &item, const QString &err);
};

#endif // PARSER_H
