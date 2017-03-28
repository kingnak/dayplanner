#ifndef OUTPUTTER_H
#define OUTPUTTER_H

#include <QObject>

class QFile;
class QTextStream;

class Outputter : public QObject
{
    Q_OBJECT
public:
    explicit Outputter(QObject *parent = 0);
    ~Outputter();

    void setOutputFile(const QString &fn);

public slots:
    void outputItem(const QString &item, const QStringList &data);
    void outputError(const QString &item, const QString &err);
    void progress(qint32 i, qint32 t);

private:
    QFile *m_file;
    QTextStream *m_str;
};

#endif // OUTPUTTER_H
