#include "news.h"

namespace testapp
{
    static const char *NEWS_API_VARIABLE_NAME = "NYTIMES_TOP_STORIES_API_KEY";
    static const char *NEWS_API_URL = "http://api.nytimes.com/svc/topstories/v1/national.json?api-key=%1";

    NewsFeed::NewsFeed(Ui_MainWindow *ui) {
        this->ui = ui;

        QProcessEnvironment pe = QProcessEnvironment::systemEnvironment();
        QString environmentKey(NEWS_API_VARIABLE_NAME);
        QString api_key = pe.value(environmentKey);

        if(api_key == QString()) {
            const char *message = "No news API key found.";
            testapp::Utility::NotifyErrorAndDie(message);
        }

        url = QString(NEWS_API_URL).arg(api_key);
        qDebug("NY Times News API URL: %s", qPrintable(url));

        connect(
            &networkManager,
            SIGNAL(error(QNetworkReply::NetworkError)),
            this,
            SLOT(newsError(QNetworkReply::NetworkError)));

        connect(
            &networkManager,
            SIGNAL(finished(QNetworkReply *)),
            this,
            SLOT(newsReceived(QNetworkReply *)));
    }

    // Initiate a news download.
    void NewsFeed::setTopItems() {

// TODO(dustin): Is there a nicer way to provide the query rather than in a complete URL?
        networkManager.get(QNetworkRequest(QString(url)));
    }

    void NewsFeed::newsError(QNetworkReply::NetworkError error)
    {
        qCritical("News response totaled resulted in error.");
    }

    // News content has been received.
    void NewsFeed::newsReceived(QNetworkReply *reply)
    {
        if(reply->error() != QNetworkReply::NoError) {
            qCritical("News response received, but error.");
            return;
        }

        QByteArray response(reply->readAll());
        QJsonObject newsResult = QJsonDocument::fromJson(response).object();

        ui->newsListWidget1->clear();

        QJsonArray articles = newsResult["results"].toArray();
        int i = 0;
        while (i < articles.size()) {
            QJsonObject o = articles[i].toObject();
            QString title = o["title"].toString();
            QString description = o["abstract"].toString();
            QString url = o["url"].toString();

            NewsListItem *item = new NewsListItem(i, title, description, url);
            ui->newsListWidget1->addItem(item);

            ++i;
        }
    }
}
