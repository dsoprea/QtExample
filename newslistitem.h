#ifndef NEWSLISTITEM_H
#define NEWSLISTITEM_H

#include <QListWidgetItem>

namespace testapp {

    // This can be added to the news list-widgets as a list-item. It describes the
    // minimum amount for any one article.
    class NewsListItem : public QListWidgetItem
    {
    public:
        NewsListItem(int index, QString title, QString description, QString url);
        const QString getUrl() const { return url; }

    private:
        int index;
        QString title;
        QString description;
        QString url;
    };
}

#endif // NEWSLISTITEM_H

