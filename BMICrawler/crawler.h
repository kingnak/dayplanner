#ifndef CRAWLER_H
#define CRAWLER_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class Crawler : public QObject
{
    Q_OBJECT
public:
    explicit Crawler(QObject *parent = 0);

    void setItems(const QStringList &items);

signals:
    void itemFinished(const QString &item, const QString &data);
    void itemProgress(qint32 cur, qint32 tot);
    void itemError(const QString &item, const QString &err);
    void crawlFinished();

public slots:
    void startCrawl();

private slots:
    void crawlNext();
    void fireFinished();
    void handleResponse(QNetworkReply *resp);

private:
    QNetworkAccessManager *m_mgr;
    QStringList m_items;
    qint32 m_idx;
    bool m_inClear;
};

#endif // CRAWLER_H
