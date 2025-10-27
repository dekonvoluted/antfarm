#include <stdexcept>

#include "grid.hpp"

// Triangles have six directions, but only three are permitted at a time
// Squares have four directions, and all are permitted at any time
// Hexagons have six directions, and all are permitted at any time
Grid::Grid(const Tiling tiling, int colors)
    : m_tiling(tiling)
    , m_colors(colors)
    , m_tiles(colors)
{
    // Cannot have fewer than two colors
    if (m_colors < 2) {
        throw std::runtime_error("Grid must have at least two colors");
    }
}

int Grid::directions() const
{
    switch (m_tiling) {
    case Tiling::TRIANGLE:
        return ::directions<Tiling::TRIANGLE>();
    case Tiling::SQUARE:
        // Square grids have four directions, and all are allowed at any time
        return 4;
    case Tiling::HEXAGON:
        return ::directions<Tiling::HEXAGON>();
    default:
        __builtin_unreachable();
    }
}

int Grid::colors() const
{
    return m_colors;
}

std::vector<std::unordered_set<Location, LocationHash>> Grid::tiles() const
{
    return m_tiles;
}

std::vector<Ant> Grid::ants() const
{
    return m_ants;
}

int Grid::generations() const
{
    return m_generations;
}

int Grid::color(Location location) const
{
    auto _color = 0;
    for (const auto& tiles : m_tiles) {
        if (tiles.find(location) != tiles.end()) {
            break;
        }
        ++_color;
    }
    if (_color == m_colors) {
        return 0;
    } else {
        return _color;
    }
}

bool Grid::valid(Location location) const
{
    switch (m_tiling) {
    case Tiling::TRIANGLE:
        return ::valid<Tiling::TRIANGLE>(location);
    case Tiling::SQUARE:
        return ::valid<Tiling::SQUARE>(location);
    case Tiling::HEXAGON:
        return ::valid<Tiling::HEXAGON>(location);
    default:
        __builtin_unreachable();
    }
}

bool Grid::valid(Heading heading, Location location) const
{
    switch (m_tiling) {
    case Tiling::TRIANGLE:
        return ::valid(heading, location);
    case Tiling::SQUARE:
    case Tiling::HEXAGON:
        return true;
    default:
        __builtin_unreachable();
    }
}

Location Grid::next(Location location, Heading heading, int steps) const
{
    switch (m_tiling) {
    case Tiling::TRIANGLE:
        return ::next<Tiling::TRIANGLE>(location, heading, steps);
    case Tiling::SQUARE:
        return ::next<Tiling::SQUARE>(location, heading, steps);
    case Tiling::HEXAGON:
        return ::next<Tiling::HEXAGON>(location, heading, steps);
    default:
        __builtin_unreachable();
    }
}

Grid& Grid::toggle(Location location)
{
    // Remove location from known colors
    auto _color = color(location);
    m_tiles[_color].erase(location);

    ++_color;
    _color %= m_colors;

    // Keep location, if color is not default
    if (_color) {
        m_tiles[_color].insert(location);
    }
    return *this;
}

Grid& Grid::ant(Location location, Heading heading)
{
    m_ants.emplace_back(Ant(*this, location, heading));
    return *this;
}
Grid& Grid::update()
{
    for (auto& ant : m_ants) {
        ant.update();
#ifndef NDEBUG
        std::cout << ant.location() << '\n';
#endif
    }

    ++m_generations;

    return *this;
}

Grid& Grid::relocate(Ant& ant, Location location)
{
    // Use friend access to private member function
    ant.move(location);

    return *this;
}

Grid& Grid::reorient(Ant& ant, Heading heading)
{
    // Use friend access to private member function
    ant.face(heading);

    return *this;
}
