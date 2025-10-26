#include <QPainter>
#include <QPixmap>

#include "scene.hpp"

const auto unit = 10;

Scene ::Scene(QObject* parent)
    : QGraphicsScene(parent)
    , m_default_tile(unit, unit)
    , m_current_tile(unit, unit)
    , m_toggled_tile(unit, unit)
    , m_grid(Tiling::SQUARE, 2)
{
    // Select colors
    m_colors = { { 0, 0xffffff }, { 1, 0x000000 } };
    // Create pixmaps
    const auto gray = 0xf0f0d0;
    m_default_tile.fill();
    m_current_tile.fill();
    m_toggled_tile.fill();

    {
        QPainter painter(&m_default_tile);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(gray));
        painter.drawRoundedRect(m_default_tile.rect().adjusted(1, 1, -1, -1), 2.0, 2.0);
    }
}

void Scene::drawBackground(QPainter* painter, const QRectF& rect)
{
    painter->drawTiledPixmap(rect, m_default_tile, rect.topLeft());
}

void Scene::drawForeground(QPainter* painter, const QRectF& rect)
{
    // Paint the toggled tiles
}
