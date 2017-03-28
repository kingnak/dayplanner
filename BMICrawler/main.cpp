#include <QCoreApplication>
#include "crawler.h"
#include "outputter.h"
#include "parser.h"

#include "rawdata.cpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Outputter o;
    o.setOutputFile("data.csv");
    Parser p;
    Crawler c;
    QStringList items = getAllItems();

    /*
    for (auto s : items) {
        if (s.contains("<<")) {
            qDebug(qPrintable(s));
        }
    }
    */

    c.setItems(items);

    QObject::connect(&c, &Crawler::crawlFinished, &a, &QCoreApplication::quit);
    QObject::connect(&c, &Crawler::itemError, &p, &Parser::parseError);
    QObject::connect(&c, &Crawler::itemFinished, &p, &Parser::parseItem);
    QObject::connect(&p, &Parser::parsed, &o, &Outputter::outputItem);
    QObject::connect(&p, &Parser::error, &o, &Outputter::outputError);
    QObject::connect(&c, &Crawler::itemProgress, &o, &Outputter::progress);

    c.startCrawl();
    a.exec();

    return 0;
}
