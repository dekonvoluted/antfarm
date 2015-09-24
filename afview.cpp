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

    auto lines = QVector<QLine>();
    lines.reserve( numSteps * numSteps );

    const auto topLeft = this->mapToScene( rect().topLeft() );
    const auto bottomRight = this->mapToScene( rect().bottomRight() );

    auto step = bottomRight.x() - topLeft.x();
    step /= numSteps;

    for ( auto x = topLeft.x(); x < bottomRight.x(); x+= step ) {
        lines << QLine( x, topLeft.y(), x, bottomRight.y() );
    }

    step = bottomRight.y() - topLeft.y();
    step /= numSteps;

    for ( auto y = topLeft.y(); y < bottomRight.y(); y += step ) {
        lines << QLine( topLeft.x(), y, bottomRight.x(), y );
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

