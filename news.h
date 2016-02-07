#ifndef NEWS_H
#define NEWS_H

#include <string>

#include <QProcessEnvironment>
#include <QString>
#include <QWidget>
#include <QUrl>
#include <QtNetwork>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QListWidget>
#include <QListWidgetItem>
#include <QtPositioning/QGeoPositionInfoSource>

#include "ui_mainwindow.h"
#include "news.h"
#include "newslistitem.h"
#include "utility.h"

namespace testapp
{
    // Describes the class that knows how to get NY Times articles.
    class NewsFeed : public QObject {
        Q_OBJECT

    public:
        NewsFeed(Ui_MainWindow *ui);
        void setNyTimesNews();

    private slots:
        void newsReceived(QNetworkReply *);

    private:
        Ui_MainWindow *ui;
        bool init;

        QString url;
        QNetworkAccessManager networkManager;
    };
}

#endif // NEWS_H
