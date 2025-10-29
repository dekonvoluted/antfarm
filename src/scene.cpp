#include <QPainter>
#include <QPixmap>

#include "scene.hpp"

// Unit must be divisible by 2, 3, 4, 6 (ideally)
const auto unit = 12;

Scene ::Scene(Tiling tiling, int colors, QObject* parent)
    : m_tiling(tiling)
    , m_colors(colors)
    , QGraphicsScene(parent)
{
    // Create grid
    m_grid = Grid(m_tiling, m_colors);

    // Select colors
    const auto gray = 0xf0f0f0;
    const auto red = 0xff0000;
    const auto green = 0x00ff00;
    const auto black = 0x000000;

    auto create = [&](QColor color, QColor fill = Qt::white, int border = 1) {
        auto pixmap = QPixmap(unit, unit);
        pixmap.fill(fill);

        QPainter painter(&pixmap);
        painter.setPen(Qt::NoPen);
        painter.setBrush(color);
        painter.drawRect(pixmap.rect().adjusted(border, border, -border, -border));

        return pixmap;
    };

    m_ant = create(QColor(red), Qt::transparent, 2);
    m_tiles[0] = create(QColor(gray));
    m_tiles[1] = create(QColor(black));
    m_tiles[2] = create(QColor(green));
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
    painter->drawTiledPixmap(rect, m_tiles[0], rect.topLeft());
}

void Scene::drawForeground(QPainter* painter, const QRectF& rect)
{
    // Mark toggled tiles
    auto color = 0;
    for (const auto& colored_tiles : m_grid.tiles()) {
        for (const auto& location : colored_tiles) {
            const auto top_left = QPointF(std::get<0>(location) * unit, std::get<1>(location) * unit);
            painter->drawPixmap(top_left, m_tiles[color]);
        }
        ++color;
    }

    // Mark ant locations
    for (const auto& ant : m_grid.ants()) {
        const auto location = ant.location();
        const auto top_left = QPointF(std::get<0>(location) * unit, std::get<1>(location) * unit);
        painter->drawPixmap(top_left, m_ant);
    }
}

#include "moc_scene.cpp"
