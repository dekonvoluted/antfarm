#include <QPainter>
#include <QPixmap>

#include "afscene.hpp"

AntFarmScene::AntFarmScene(QObject* parent)
    : QGraphicsScene(parent)
    , whiteSquare(10, 10)
    , blackSquare(10, 10)
{
    // Create pixmap for white square
    whiteSquare.fill();
    QPainter whitePainter(&whiteSquare);
    whitePainter.setPen(Qt::NoPen);
    whitePainter.setBrush(QColor(240, 240, 240));
    whitePainter.drawRoundedRect(whiteSquare.rect().adjusted(1, 1, -1, -1), 2.0, 2.0);

    // Create pixmap for black squares
    blackSquare.fill();
    QPainter blackPainter(&blackSquare);
    blackPainter.setPen(Qt::NoPen);
    blackPainter.setBrush(QColor(160, 160, 160));
    blackPainter.drawRoundedRect(blackSquare.rect().adjusted(1, 1, -1, -1), 2.0, 2.0);
}

void AntFarmScene::drawBackground(QPainter* painter, const QRectF& rect)
{
    // Draw the background squares
    painter->drawTiledPixmap(rect, whiteSquare, rect.topLeft());
}

void AntFarmScene::drawForeground(QPainter* painter, const QRectF& rect)
{
    // Color in the changed squares
    for (auto point : flippedSquares) {
        painter->drawPixmap(point, blackSquare);
    }
}
