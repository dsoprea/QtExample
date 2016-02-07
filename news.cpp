#include "news.h"

namespace testapp {
    const char *NEWS_API_VARIABLE_NAME = "NYTIMES_TOP_STORIES_API_KEY";
    const char *NEWS_API_URL = "http://api.nytimes.com/svc/topstories/v1/national.json?api-key=%1";

    NewsFeed::NewsFeed() {
        QProcessEnvironment pe = QProcessEnvironment::systemEnvironment();
        QString environmentKey(NEWS_API_VARIABLE_NAME);
        QString api_key = pe.value(environmentKey);

        if(api_key == QString()) {
            const char *message = "No news API key found.";
            Utility::NotifyErrorAndDie(message);
        }

        url = QString(NEWS_API_URL).arg(api_key);
    }

    // Initiate a news download.
    void NewsFeed::setTopItems() {
        connect(&networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(newsReceived(QNetworkReply *)));

    // TODO(dustin): Is there a nicer way to provide the query rather than in a complete URL?
        networkManager.get(QNetworkRequest(QString(url)));
    }

    // News content has been received.
    void NewsFeed::newsReceived(QNetworkReply *)
    {
        int a = 5;

    }
}
