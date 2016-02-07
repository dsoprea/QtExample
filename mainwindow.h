#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QUrl>
#include <QWebFrame>
#include <QWebElementCollection>
#include <QListWidget>
#include <QListWidgetItem>

#include "news.h"

namespace Ui {
class MainWindow;
}

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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_readNews_clicked();
    void on_loadWebpage_clicked();

    void on_webView_loadFinished(bool arg1);

    void on_newsListWidget2_itemActivated(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QStringListModel *news1ListSource;
    QStringListModel *news2ListSource;
    testapp::NewsFeed newsFeed;

    void extractAndPopulateYahooNewsItems();
};

#endif // MAINWINDOW_H
