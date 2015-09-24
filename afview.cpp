#include <QLine>
#include <QtMath>
#include <QWheelEvent>
#include <QVector>

#include "afview.h"
#include "afscene.h"

AntFarmView::AntFarmView( AntFarmScene* afscene, QWidget* parent ) : QGraphicsView( afscene, parent ), scene( afscene )
{
    this->setRenderHints( QPainter::Antialiasing );
}

void AntFarmView::drawForeground( QPainter* painter, const QRectF& rectangle )
{
    painter->setPen( Qt::yellow );

    const auto numSteps = 100;

    auto lines = QVector<QLine>();
    lines.reserve( numSteps * numSteps );

    auto step = 1200;
    step /= numSteps;

    for ( auto x = -300; x < 900; x+= step ) {
        lines << QLine( x, -300, x, 900 );
    }

    step = 1200;
    step /= numSteps;

    for ( auto y = -300; y < 900; y += step ) {
        lines << QLine( -300, y, 900, y );
    }

    painter->drawLines( lines );

    QGraphicsView::drawForeground( painter, rectangle );
}

void AntFarmView::wheelEvent( QWheelEvent* event )
{
    auto degrees = event->angleDelta();
    degrees /= 8;
    degrees /= 15;

    this->rotate( degrees.y() );
    this->scale( qPow( 1.1, degrees.y() ), qPow( 1.1, degrees.y() ) );

    QGraphicsView::wheelEvent( event );
}

