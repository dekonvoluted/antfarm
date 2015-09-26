#include <QToolBar>

#include "afmainwindow.h"
#include "afscene.h"
#include "afview.h"
#include "fpswidget.h"

AntFarmMainWindow::AntFarmMainWindow( QWidget* parent ) : QMainWindow( parent )
{
    auto toolbar = new QToolBar( "FPS Toolbar" );

    auto fps = new FPSWidget;
    toolbar->addWidget( fps );
    connect( toolbar, SIGNAL( orientationChanged( Qt::Orientation ) ), fps, SLOT( setOrientation( Qt::Orientation ) ) );

    this->addToolBar( toolbar );

    scene = new AntFarmScene();
    view = new AntFarmView( scene );

    this->setCentralWidget( view );
}

