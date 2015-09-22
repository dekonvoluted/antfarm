#include "afmainwindow.h"
#include "afscene.h"
#include "afview.h"

AntFarmMainWindow::AntFarmMainWindow( QWidget* parent ) : QMainWindow( parent )
{
    scene = new AntFarmScene();
    view = new AntFarmView( scene );

    this->setCentralWidget( view );
}

