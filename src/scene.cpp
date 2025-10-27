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
    const auto gray = 0xf0f0f0;
    const auto red = 0xff0000;
    const auto black = 0x000000;

    m_default_tile.fill();
    m_current_tile.fill(Qt::transparent);
    m_toggled_tile.fill();

    {
        QPainter painter(&m_default_tile);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(gray));
        painter.drawRect(m_default_tile.rect().adjusted(1, 1, -1, -1));
    }

    {
        QPainter painter(&m_current_tile);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(red));
        painter.drawRect(m_current_tile.rect().adjusted(2, 2, -2 , -2));
    }

    {
        QPainter painter(&m_toggled_tile);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(black));
        painter.drawRect(m_toggled_tile.rect().adjusted(1, 1, -1, -1));
    }
}

void Scene::ant()
{
    m_grid.ant();
    QGraphicsScene::update();
}

void Scene::step()
{
    m_grid.update();
    QGraphicsScene::update();
    emit stepped(m_grid.generations());
}

void Scene::drawBackground(QPainter* painter, const QRectF& rect)
{
    painter->drawTiledPixmap(rect, m_default_tile, rect.topLeft());
}

void Scene::drawForeground(QPainter* painter, const QRectF& rect)
{
    // Mark toggled tiles
    for (const auto& colored_tiles : m_grid.tiles()) {
        for (const auto& location : colored_tiles) {
            const auto top_left = QPointF(std::get<0>(location) * unit, std::get<1>(location) * unit);
            painter->drawPixmap(top_left, m_toggled_tile);
        }
    }

    // Mark ant locations
    for (const auto& ant : m_grid.ants()) {
        const auto location = ant.location();
        const auto top_left = QPointF(std::get<0>(location) * unit, std::get<1>(location) * unit);
        painter->drawPixmap(top_left, m_current_tile);
    }
}

#include "moc_scene.cpp"
