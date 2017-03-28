#include "outputter.h"
#include <QDebug>
#include <QTextStream>
#include <QFile>

Outputter::Outputter(QObject *parent)
    : QObject(parent),
      m_file(nullptr),
      m_str(nullptr)
{

}

Outputter::~Outputter()
{
    delete m_str;
    delete m_file;
}

void Outputter::setOutputFile(const QString &fn)
{
    if (m_file) {
        delete m_str;
        delete m_file;
        m_file = nullptr;
        m_str = nullptr;
    }

    m_file = new QFile(fn);
    if (!m_file->open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        delete m_file;
        m_file = nullptr;
        return;
    }

    m_str = new QTextStream(m_file);
    m_str->setCodec("utf-8");
}

void Outputter::outputItem(const QString &item, const QStringList &data)
{
    if (!m_file)
        qDebug().noquote() << item << ";" << data.join(";");
    else {
        (*m_str) << item << ";" << data.join(";") << "\n";
        m_str->flush();
    }
}

void Outputter::outputError(const QString &item, const QString &err)
{
    qDebug().noquote() << item << err;
}

void Outputter::progress(qint32 i, qint32 t)
{
    qDebug().noquote() << i << " / " << t;
}
