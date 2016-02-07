#include "mainwindow.h"
#include "ui_mainwindow.h"

static QString rootUrl("http://news.yahoo.com");

NewsListItem::NewsListItem(int index, QString title, QString description, QString url) {
    this->index = index;
    this->title = title;
    this->description = description;
    this->url = url;

    setText(QString::number(index) + QString(": ") + title);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    news1ListSource = new QStringListModel(this);
    ui->newsView1->setModel(news1ListSource);
}

MainWindow::~MainWindow()
{
    delete news1ListSource;
    delete news2ListSource;

    delete ui;
}

void MainWindow::on_readNews_clicked()
{
    QStringList list;
    list << "item1";
    list << "item2";
    list << "item3";

    news1ListSource->setStringList(list);

//    std::cout << "Hello." << std::endl;
    //ui->listView1->
//    new QListViewItem( ui->listView1, "(1, 1)", "(1, 2)", "(1, 3)" );

//    ui->listView1->addColumn( "Foo" );
//    ui->listView1->addColumn( "Bar" );
//    ui->listView1->addColumn( "Baz" );

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

        NewsListItem *item = new NewsListItem(i, title, description, url);
        ui->newsListWidget2->addItem(item);

        i++;
    }
}

// A Yahoo news item was double-clicked.
void MainWindow::on_newsListWidget2_itemActivated(QListWidgetItem *item)
{
    NewsListItem *proper = (NewsListItem *)item;
    ui->webView->setUrl(QUrl(rootUrl + proper->getUrl()));
}
