#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QUrl>
#include <QWebFrame>
#include <QWebElementCollection>
#include <QListWidgetItem>
#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>

// NOTE
//
// We manually added this, removed the "Ui" namespace block, and replaced occurrences of
// Ui::MainWindow with Ui_MainWindow. The default construction isn't reflected in any of
// the examples and we're encountering unexplanable build errors when adding new fields
// to MainWindow.

#include "ui_mainwindow.h"
#include "news.h"
#include "newslistitem.h"

QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceDiscoveryAgent)
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_readNyTimesNews_clicked();
    void on_loadWebpage_clicked();
    void on_webView_loadFinished(bool arg1);
    void on_newsListWidget1_itemActivated(QListWidgetItem *item);
    void on_newsListWidget2_itemActivated(QListWidgetItem *item);
    void on_scanBluetooth_clicked();

    void addDevice(const QBluetoothDeviceInfo &info);
    void scanFinished();

private:

// NOTE(dustin): This is a type generated automatically based on the name of the form.
    Ui_MainWindow *ui;

    testapp::NewsFeed newsFeed;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;

    void extractAndPopulateYahooNewsItems();
};

#endif // MAINWINDOW_H
