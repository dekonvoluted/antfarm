#include <vector>

#include <QPainter>
#include <QPixmap>

#include "scene.hpp"

// Unit must be divisible by 2, 3, and 6 (ideally)
const auto unit = 12;

Scene ::Scene(Tiling tiling, int colors, QObject* parent)
    : m_tiling(tiling)
    , m_colors(colors)
    , QGraphicsScene(parent)
{
    // Create grid
    m_grid = Grid(m_tiling, m_colors);

    // Select colors
    const auto red = QColor(0xff0000);
    const std::vector<QColor> palette = {
        0xf5f5f5,
        0x3d81b8,
        0xff7d00,
        0x094e86,
        0x001524
    };
    const std::map<int, std::map<int, int>> colorpalette = {
        { 2, { { 0, 0 }, { 1, 4 } } },
        { 3, { { 0, 0 }, { 1, 2 }, { 2, 4 } } },
        { 4, { { 0, 0 }, { 1, 1 }, { 2, 3 }, { 3, 4 } } },
        { 5, { { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 } } }
    };

    auto square = [&](QColor color, QColor fill = Qt::transparent, int border = 1) {
        auto pixmap = QPixmap(unit, unit);
        pixmap.fill(fill);

        QPainter painter(&pixmap);
        painter.setPen(Qt::NoPen);
        painter.setBrush(color);
        painter.drawRect(pixmap.rect().adjusted(border, border, -border, -border));

        return pixmap;
    };

    auto hexagon = [&](QColor color, QColor fill = Qt::transparent, int border = 1) {
        auto pixmap = QPixmap(2.0 * unit / 3.0, unit);
        pixmap.fill(fill);

        QPainter painter(&pixmap);
        painter.setPen(Qt::NoPen);
        painter.setBrush(color);

        QTransform shrink;
        const auto factor = 1.0 - 1.0 * border / unit;
        shrink.scale(factor, factor);
        painter.setTransform(shrink);

        QPolygonF polygon;
        polygon
            << QPointF(0.0, unit / 3.0)
            << QPointF(0.0, 2.0 * unit / 3.0)
            << QPointF(unit / 3.0, 5.0 * unit / 6.0)
            << QPointF(2.0 * unit / 3.0, 2.0 * unit / 3.0)
            << QPointF(2.0 * unit / 3.0, unit / 3.0)
            << QPointF(unit / 3.0, unit / 6.0);
        painter.drawConvexPolygon(polygon);

        return pixmap;
    };

    if (m_tiling == Tiling::HEXAGON) {
        m_tiles[0] = [&]() {
            auto pixmap = QPixmap(2.0 * unit / 3.0, unit);
            pixmap.fill();

            const auto color = palette.at(colorpalette.at(colors).at(0));
            auto hexmap = hexagon(color);

            QPainter painter(&pixmap);
            painter.drawPixmap(0, 0, hexmap);
            painter.drawPixmap(-unit / 3.0, unit / 2.0, hexmap);
            painter.drawPixmap(-unit / 3.0, -unit / 2.0, hexmap);
            painter.drawPixmap(unit / 3.0, unit / 2.0, hexmap);
            painter.drawPixmap(unit / 3.0, -unit / 2.0, hexmap);

            return pixmap;
        }();
    }

    switch (m_tiling) {
    case Tiling::SQUARE:
        m_ant = square(red, Qt::transparent, 2);
        for (auto color = 0; color < colors; ++color) {
            m_tiles[color] = square(palette.at(colorpalette.at(colors).at(color)));
        }
        break;
    case Tiling::HEXAGON:
        m_ant = hexagon(red, Qt::transparent, 2);
        for (auto color = 1; color < colors; ++color) {
            m_tiles[color] = hexagon(palette.at(colorpalette.at(colors).at(color)));
        }
        break;
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
    painter->drawTiledPixmap(rect, m_tiles[0], rect.topLeft());
}

void Scene::drawForeground(QPainter* painter, const QRectF& rect)
{
    auto squareLocation = [&](const Location& location) {
        return QPointF(std::get<0>(location) * unit, std::get<1>(location) * unit);
    };

    auto hexagonLocation = [&](const Location& location) {
        return QPointF((std::get<0>(location) - std::get<2>(location)) * unit / 3.0, std::get<1>(location) * unit / 2.0);
    };
    // Mark toggled tiles
    auto color = 0;
    for (const auto& colored_tiles : m_grid.tiles()) {
        for (const auto& location : colored_tiles) {
            switch (m_tiling) {
            case Tiling::SQUARE:
                painter->drawPixmap(squareLocation(location), m_tiles[color]);
                break;
            case Tiling::HEXAGON:
                painter->drawPixmap(hexagonLocation(location), m_tiles[color]);
                break;
            }
        }
        ++color;
    }

    // Mark ant locations
    for (const auto& ant : m_grid.ants()) {
        const auto location = ant.location();
        switch (m_tiling) {
        case Tiling::SQUARE:
            painter->drawPixmap(squareLocation(location), m_ant);
            break;
        case Tiling::HEXAGON:
            painter->drawPixmap(hexagonLocation(location), m_ant);
            break;
        }
    }
}

#include "moc_scene.cpp"
