#ifndef NEWS_H
#define NEWS_H

#include <string>

#include <QProcessEnvironment>
#include <QString>
#include <QWidget>
#include <QUrl>

#include <QtNetwork>

#include "news.h"
#include "utility.h"

namespace testapp {
    class NewsFeed : public QObject {
        Q_OBJECT

    public:
        NewsFeed();
        void setTopItems();

    public slots:
        void newsReceived(QNetworkReply *);

    private:
        QString url;
        QNetworkAccessManager networkManager;
    };
}

#endif // NEWS_H

