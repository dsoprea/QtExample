#include "mainwindow.h"
#include "ui_mainwindow.h"

static QString rootUrl("http://news.yahoo.com");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui_MainWindow),
    newsFeed(ui)
{
    ui->setupUi(this);

//    newsFeed = new testapp::NewsFeed();
}

MainWindow::~MainWindow()
{
//    delete newsFeed;
    delete ui;
}

void MainWindow::on_readNews_clicked()
{
    newsFeed.setTopItems();
}

// Load webpage.
void MainWindow::on_loadWebpage_clicked()
{
    ui->webView->setUrl(QUrl(rootUrl));
}

// Web content has loaded.
void MainWindow::on_webView_loadFinished(bool)
{
    extractAndPopulateYahooNewsItems();
}

void MainWindow::extractAndPopulateYahooNewsItems()
{
    QWebFrame *frame = ui->webView->page()->mainFrame();

    QWebElement document = frame->documentElement();
    QString selector("#Main li.content .body");
    QWebElementCollection elements = document.findAll(selector);

    ui->newsListWidget2->clear();
    int i = 0;
    foreach (QWebElement element, elements) {
        QString titleSelector("a");
        QWebElement titleElement = element.findFirst(titleSelector);
        QString title = titleElement.toPlainText();
        QString url = titleElement.attribute("href");

        QString descriptionSelector(".summary");
        QWebElement descriptionElement = element.findFirst(descriptionSelector);
        QString description = descriptionElement.toPlainText();

        testapp::NewsListItem *item = new testapp::NewsListItem(i, title, description, rootUrl + url);
        ui->newsListWidget2->addItem(item);

        i++;
    }
}

// A NY Times news item was double-clicked.
void MainWindow::on_newsListWidget1_itemActivated(QListWidgetItem *item)
{
    testapp::NewsListItem *proper = (testapp::NewsListItem *)item;
    ui->webView->setUrl(QUrl(proper->getUrl()));
}

// A Yahoo news item was double-clicked.
void MainWindow::on_newsListWidget2_itemActivated(QListWidgetItem *item)
{
    testapp::NewsListItem *proper = (testapp::NewsListItem *)item;
    ui->webView->setUrl(QUrl(proper->getUrl()));
}
