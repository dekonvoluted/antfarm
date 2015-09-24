#include <QLine>
#include <QtMath>
#include <QWheelEvent>
#include <QVector>

#include "afview.h"
#include "afscene.h"

AntFarmView::AntFarmView( AntFarmScene* afscene, QWidget* parent ) : QGraphicsView( afscene, parent ), scene( afscene )
{}

void AntFarmView::drawForeground( QPainter* painter, const QRectF& rectangle )
{
    painter->setPen( Qt::yellow );

    const auto numSteps = 100;

    auto step = sceneRect().right() - sceneRect().left();
    step /= numSteps;

    auto lines = QVector<QLine>();
    lines.reserve( numSteps * numSteps );

    for ( auto x = sceneRect().left(); x < sceneRect().right(); x += step ) {
        lines << QLine( x, sceneRect().top(), x, sceneRect().bottom() );
    }

    step = sceneRect().bottom() - sceneRect().top();
    step /= numSteps;

    for ( auto y = sceneRect().top(); y < sceneRect().bottom(); y += step ) {
        lines << QLine( sceneRect().left(), y, sceneRect().right(), y );
    }

    painter->drawLines( lines );

    QGraphicsView::drawForeground( painter, rectangle );
}

void AntFarmView::wheelEvent( QWheelEvent* event )
{
    auto degrees = event->angleDelta();
    degrees /= 8;
    degrees /= 15;

    this->scale( qPow( 1.1, degrees.y() ), qPow( 1.1, degrees.y() ) );
    QGraphicsView::wheelEvent( event );
}

