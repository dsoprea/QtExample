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

#include "ui_mainwindow.h"
#include "news.h"
#include "newslistitem.h"
#include "utility.h"

namespace testapp
{
    class NewsFeed : public QObject {
        Q_OBJECT

    public:
        NewsFeed(Ui_MainWindow *ui);
        void setTopItems();

    public slots:
        void newsReceived(QNetworkReply *);
        void newsError(QNetworkReply::NetworkError);

    private:
        Ui_MainWindow *ui;

        QString url;
        QNetworkAccessManager networkManager;
    };
}

#endif // NEWS_H
