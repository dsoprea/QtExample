#include "mainwindow.h"
#include <QApplication>

QApplication *app;
MainWindow *rootWindow;

int main(int argc, char *argv[])
{
    app = new QApplication(argc, argv);
    rootWindow = new MainWindow();
    rootWindow->show();

    int result = app->exec();
    delete rootWindow;
    delete app;

    return result;
}
