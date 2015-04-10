#include "core.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    core mainApp;
    return app.exec();
}
