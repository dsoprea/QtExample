#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow rootWindow;
    rootWindow.show();

    return app.exec();
}
