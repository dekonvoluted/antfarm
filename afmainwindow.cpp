#include "afmainwindow.h"
#include "afview.h"

AntFarmMainWindow::AntFarmMainWindow( QWidget* parent ) : QMainWindow( parent )
{
    view = new AntFarmView();

    this->setCentralWidget( view );
}

