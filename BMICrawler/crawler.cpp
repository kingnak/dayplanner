#include "crawler.h"
#include <QtNetwork>

Crawler::Crawler(QObject *parent)
    : QObject(parent),
      m_mgr(nullptr),
      m_idx(0),
      m_inClear(false)
{
}

void Crawler::setItems(const QStringList &items)
{
    m_items = items;
}

void Crawler::startCrawl()
{
    if (!m_mgr) {
        m_mgr = new QNetworkAccessManager(this);
        connect(m_mgr, &QNetworkAccessManager::finished, this, &Crawler::handleResponse);
    }

    m_idx = 0;
    m_inClear = false;
    if (m_items.empty()) {
        QTimer::singleShot(0, this, &Crawler::fireFinished);
    } else {
        QTimer::singleShot(0, this, &Crawler::crawlNext);
    }
}

void Crawler::crawlNext()
{
    QNetworkRequest req(QUrl("http://www.bmi-rechner.net/cgi-bin/kalorienrechner.cgi"));
    req.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/x-www-form-urlencoded; charset=UTF-8");
    QByteArray data = QString("lebensmittel_drop_[1]=undefined&menge_[1]=10000&lebensmittel_[1]=%1").arg(m_items[m_idx]).toUtf8();

    m_inClear = false;
    m_mgr->post(req, data);
}

void Crawler::handleResponse(QNetworkReply *resp)
{
    resp->deleteLater();
    if (m_inClear) {
        m_inClear = false;
        if (++m_idx >= m_items.size()) {
            fireFinished();
        } else {
            emit itemProgress(m_idx, m_items.size());
            QTimer::singleShot(1000, this, &Crawler::crawlNext);
        }
        return;
    }

    //QString contentType = resp->header(QNetworkRequest::KnownHeaders::ContentTypeHeader).toString();
    //QString encoding = "ISO-8859-1";
    QString s = QString::fromLatin1(resp->readAll());


    if (resp->error() != QNetworkReply::NetworkError::NoError) {
        emit itemError(m_items[m_idx], resp->errorString() + "\n" + s);
    } else {
        emit itemFinished(m_items[m_idx], s);
    }

    m_inClear = true;
    m_mgr->get(QNetworkRequest(QUrl("http://www.bmi-rechner.net/cgi-bin/kalorienrechner_update.cgi?modus=listeloeschen")));
}

void Crawler::fireFinished()
{
    emit itemProgress(m_items.size(), m_items.size());
    emit crawlFinished();
}
