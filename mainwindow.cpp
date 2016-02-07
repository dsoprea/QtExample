#include "mainwindow.h"
#include "ui_mainwindow.h"

static QString rootUrl("http://news.yahoo.com");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui_MainWindow),
    newsFeed(ui)
{
    ui->setupUi(this);

    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();

    connect(
        discoveryAgent,
        SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
        this,
        SLOT(addDevice(QBluetoothDeviceInfo)));

    connect(
        discoveryAgent,
        SIGNAL(finished()),
        this,
        SLOT(scanFinished()));

    gpsSource = QGeoPositionInfoSource::createDefaultSource(this);
    if(gpsSource == NULL)
    {
        const char *message = "No location sources exist.";

        qCritical(message);
        ui->gpsPosition->setText(message);

        QStringList sources = QGeoPositionInfoSource::availableSources();
        if(sources.empty() == false) {
            QString firstSource = sources[0];
            qWarning("GPS not available, but we found another source: [%s]", qPrintable(firstSource));
            gpsSource = QGeoPositionInfoSource::createSource(firstSource, this);
        }
    }

    if(gpsSource != NULL) {
        connect(
            gpsSource,
            SIGNAL(positionUpdated(QGeoPositionInfo)),
            this,
            SLOT(positionUpdated(QGeoPositionInfo)));

        connect(
            gpsSource,
            SIGNAL(error(QGeoPositionInfoSource::Error)),
            this,
            SLOT(positionError(QGeoPositionInfoSource::Error)));

        gpsSource->startUpdates();
    }
}

// A new position has been reported.
void MainWindow::positionUpdated(QGeoPositionInfo gpsPos)
{
    QGeoCoordinate coord = gpsPos.coordinate();
    ui->gpsPosition->setText(QString::number(coord.latitude()) + QString(", ") + QString::number(coord.longitude()));
}

// There was a problem getting the position.
void MainWindow::positionError(QGeoPositionInfoSource::Error)
{
    ui->gpsPosition->setText("There was an error getting the position.");
}

MainWindow::~MainWindow()
{
    if(gpsSource)
    {
        gpsSource->stopUpdates();
        delete gpsSource;
    }

    delete ui;
}

// Initiate a Bluetooth scan.
void MainWindow::on_scanBluetooth_clicked()
{
    discoveryAgent->start();
}

// Respond to the signal telling us that a device was found and add it to the list.
void MainWindow::addDevice(const QBluetoothDeviceInfo &info)
{
    QString label = QString("%1 %2").arg(info.address().toString()).arg(info.name());

    // Only add if it's not already in the list. There must be a chance of us being called
    // multiple times.

    QList<QListWidgetItem *> items = ui->bluetoothDevices->findItems(label, Qt::MatchExactly);
    if (items.empty()) {
        QListWidgetItem *item = new QListWidgetItem(label);
        ui->bluetoothDevices->addItem(item);
    }
}

// The Bluetooth scan has finished.
void MainWindow::scanFinished()
{

}

// Respond to the button click on load the NY Times news.
void MainWindow::on_readNyTimesNews_clicked()
{
    newsFeed.setNyTimesNews();
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

// The Yahoo webpage has loaded. Mine the content to grab a list of news items.
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
    qDebug("NY Times article activated.");

    testapp::NewsListItem *proper = (testapp::NewsListItem *)item;
    ui->webView->setUrl(QUrl(proper->getUrl()));
}

// A Yahoo news item was double-clicked.
void MainWindow::on_newsListWidget2_itemActivated(QListWidgetItem *item)
{
    qDebug("Yahoo article activated.");

    testapp::NewsListItem *proper = (testapp::NewsListItem *)item;
    ui->webView->setUrl(QUrl(proper->getUrl()));
}
