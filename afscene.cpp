#include "afscene.h"

AntFarmScene::AntFarmScene( QObject* parent ) : QGraphicsScene( parent )
{
    this->setSceneRect( 0, 0, 600, 600 );

    setBackgroundBrush( Qt::black );

    this->addRect( QRectF( 300, 300, 100, 100 ), QPen( Qt::white ), QBrush( Qt::green ) );
}

