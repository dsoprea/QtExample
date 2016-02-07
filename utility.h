#ifndef UTILITY_H
#define UTILITY_H

#include <QString>
#include <QMessageBox>
#include <QApplication>

namespace testapp {
    class Utility {
    public:
        static void NotifyErrorAndDie(const char *message);
    };
}

#endif // UTILITY_H
