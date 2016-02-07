#ifndef NEWSLISTITEM_H
#define NEWSLISTITEM_H

#include <QListWidgetItem>

namespace testapp {
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

