#ifndef AF_SCENE_H
#define AF_SCENE_H

#include <QGraphicsScene>

class QPainter;
class QPixmap;

class AntFarmScene : public QGraphicsScene
{
    public:
    AntFarmScene( QObject* = 0 );

    protected:
    void drawBackground( QPainter*, const QRectF& );
    void drawForeground( QPainter*, const QRectF& );

    private:
    QList<QPoint> flippedSquares;

    QPixmap whiteSquare;
    QPixmap blackSquare;
};

#endif

