#include <QApplication>

#include "afmainwindow.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    AntFarmMainWindow* mainWindow = new AntFarmMainWindow();
    mainWindow->show();

    return app.exec();
}
