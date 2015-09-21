#include <QApplication>

#include "afmainwindow.h"

int main( int argc, char** argv )
{
    QApplication app( argc, argv );

    AntFarmMainWindow* mainWindow = new AntFarmMainWindow();
    mainWindow->show();

    return app.exec();
}

