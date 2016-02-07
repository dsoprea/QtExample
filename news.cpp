#include "news.h"

namespace testapp
{
    static const char *NEWS_API_VARIABLE_NAME = "NYTIMES_TOP_STORIES_API_KEY";
    static const char *NEWS_API_URL = "http://api.nytimes.com/svc/topstories/v1/national.json?api-key=%1";

    NewsFeed::NewsFeed(Ui_MainWindow *ui) : init(false) {
        this->ui = ui;

        QProcessEnvironment pe = QProcessEnvironment::systemEnvironment();
        QString environmentKey(NEWS_API_VARIABLE_NAME);
        QString api_key = pe.value(environmentKey);

        if(api_key == QString()) {
            qCritical("No news API key found.");
            return;
        }

        url = QString(NEWS_API_URL).arg(api_key);
        qDebug("NY Times News API URL: %s", qPrintable(url));

        connect(
            &networkManager,
            SIGNAL(finished(QNetworkReply *)),
            this,
            SLOT(newsReceived(QNetworkReply *)));

        init = true;
    }

    // Initiate a news download.
    void NewsFeed::setNyTimesNews() {
        if(init == true)
        {
            qDebug("Setting NY Times news.");

// TODO(dustin): Is there a nicer way to provide the query rather than in a complete URL?
            networkManager.get(QNetworkRequest(QString(url)));
        }
    }

    // News content has been received.
    void NewsFeed::newsReceived(QNetworkReply *reply)
    {
        if(reply->error() != QNetworkReply::NoError) {
            qCritical("NY Times news response received, but error.");
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
