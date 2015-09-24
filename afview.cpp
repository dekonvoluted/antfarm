#include <QtMath>
#include <QWheelEvent>

#include "afview.h"
#include "afscene.h"

AntFarmView::AntFarmView( AntFarmScene* afscene, QWidget* parent ) : QGraphicsView( afscene, parent ), scene( afscene )
{}

void AntFarmView::wheelEvent( QWheelEvent* event )
{
    auto degrees = event->angleDelta();
    degrees /= 8;
    degrees /= 15;

    this->scale( qPow( 1.1, degrees.y() ), qPow( 1.1, degrees.y() ) );
    QGraphicsView::wheelEvent( event );
}

