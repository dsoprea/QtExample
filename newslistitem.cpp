#include "newslistitem.h"

namespace testapp {
    NewsListItem::NewsListItem(int index, QString title, QString description, QString url) {
        this->index = index;
        this->title = title;
        this->description = description;
        this->url = url;

        setText(QString::number(index) + QString(": ") + title);
    }
}
