#include "utility.h"
#include "mainwindow.h"

extern QApplication *app;
extern MainWindow *rootWindow;

namespace testapp {
    void Utility::NotifyErrorAndDie(const char *message) {
        QString title("Application Error");
        QString text(message);

    // TODO(dustin): Debug why this doesn't present a popup.
        QMessageBox(QMessageBox::Critical, title, text, QMessageBox::NoButton, rootWindow);

        qCritical(message);
    // TODO(dustin): Debug why this doesn't terminate (it used to).
        app->quit();
    }
}
