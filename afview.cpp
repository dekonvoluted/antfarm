#include <QtMath>
#include <QWheelEvent>

#include "afview.h"
#include "afscene.h"

AntFarmView::AntFarmView( AntFarmScene* afscene, QWidget* parent ) : QGraphicsView( afscene, parent ), scene( afscene )
{}

void AntFarmView::paintEvent( QPaintEvent* event )
{
    const auto numSteps = 10;

    auto step = sceneRect().right() - sceneRect().left();
    step /= numSteps;

    for ( auto x = sceneRect().left(); x < sceneRect().right(); x += step ) {
        scene->addLine( QLine( x, sceneRect().top(), x, sceneRect().bottom() ), QPen( Qt::yellow ) );
    }

    step = sceneRect().bottom() - sceneRect().top();
    step /= numSteps;

    for ( auto y = sceneRect().top(); y < sceneRect().bottom(); y += step ) {
        scene->addLine( QLine( sceneRect().left(), y, sceneRect().right(), y ), QPen( Qt::yellow ) );
    }

    QGraphicsView::paintEvent( event );
}

void AntFarmView::wheelEvent( QWheelEvent* event )
{
    auto degrees = event->angleDelta();
    degrees /= 8;
    degrees /= 15;

    this->scale( qPow( 1.1, degrees.y() ), qPow( 1.1, degrees.y() ) );
    QGraphicsView::wheelEvent( event );
}

