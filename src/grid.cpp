#include <stdexcept>

#include "ant.hpp"
#include "grid.hpp"

// Triangles have six directions, but only three are permitted at a time
// Squares have four directions, and all are permitted at any time
// Hexagons have six directions, and all are permitted at any time
Grid::Grid(const Tiling tiling, int colors) : m_tiling(tiling), m_directions(6), m_colors(colors), m_tiles(colors, {})
{
    if (m_tiling == Tiling::SQUARE) {
        const_cast<int&>(m_directions) = 4;
    }

    // Cannot have fewer than two colors
    if (m_colors < 2) {
        throw std::runtime_error("Grid must have at least two colors");
    }
}

int Grid::directions() const
{
    return m_directions;
}

int Grid::colors() const
{
    return m_colors;
}

bool Grid::valid(Location location) const
{
    const auto [p, q, r] = location;
    switch (m_tiling) {
        case Tiling::TRIANGLE:
            // Triangle tiling has left- and right-pointing triangles
            // Left-pointing triangles have r = 0
            // Right-pointing triangles have r = 1
            return r == 0 or r == 1;
        case Tiling::SQUARE:
            // Square tiling disregards third coordinate
            return r == 0;
        case Tiling::HEXAGON:
            // Hexagon tiling preserves an invariant
            return p + q + r == 0;
    }
}

bool Grid::valid(Heading heading, Location location) const
{
    if (heading < 0) {
        return false;
    }

    if (heading >= m_directions) {
        return false;
    }

    // Triangular tiling needs additional checks based on location
    // Left-pointing triangles have r = 0 and allow 0, 2, 4 headings
    // Right-pointing triangles have r = 1 and allow 1, 3, 5 headings
    if (m_tiling != Tiling::TRIANGLE) {
        return true;
    }

    const auto [p, q, r] = location;
    return (heading % 2) == r;
}


Grid& Grid::ant(Location location, Heading heading) {
    if (not valid(location)) {
        std::runtime_error("Unable to create ant at invalid location");
    }
    if (not valid(location, heading)) {
        std::runtime_error("Unable to create ant with invalid heading");
    }

    m_ants.emplace_back(Ant(*this, location, heading));
    return *this;
}

int Grid::color(Location location) const
{
    auto color = 0;
    for (const auto& tiles : m_tiles) {
        if (tiles.find(location) != tiles.end()) {
            break;
        }
        ++color;
    }
    return color;
}

Grid& Grid::toggle(Location location) {
    // Remove location from known colors
    const auto color = color(location);
    m_tiles[color].erase(location);

    ++color;
    color %= m_colors;

    // Keep location, if color is not default
    if (color) {
        m_tiles[color].insert(location);
    }
}

Grid& move(Ant& ant, int step)
{
}




Grid& place(Ant& ant, Location location)
{
    ant.go(location);

    // Ant can do these checks:
    if (not valid(location)) {
        std::runtime_error("Unable to move ant to invalid location");
    }

    // Heading may be invalid on triangular grids
    if (not valid(location, heading)) {
        std::runtime_error("Unable to move ant to location where heading is not allowed.");
    }

    // Use friend access to private member function
    ant.go(location);
}

Location Grid::where(Location location, Heading heading, int step) const
{
    // Assume location and heading are both valid

    auto& [p, q, r] = location;

    switch (m_tiling) {
        case Tiling::TRIANGLE:
            // NOTE - Heading may no longer be valid at new location

            // Only allow one step for triangles
            if (step < -1 or step > 1) {
                throw std::runtime_error("Unable to take more than one step for triangles");
            }

            // Toggle left-/right-pointedness
            if (step != 0) {
                r = not r;
            }

            switch (heading) {
                case 0:
                    break;
                case 1:
                    p += step;
                    break;
                case 2:
                    q += step;
                    break;
                case 3:
                    break;
                case 4:
                    p -= step;
                    break;
                case 5:
                    q -= step;
                    break;
            }
            break;
        case Tiling::SQUARE:
            switch (heading) {
                case 0:
                    p += step;
                    break;
                case 1:
                    q += step;
                    break;
                case 2:
                    p -= step;
                    break;
                case 3:
                    q -= step;
                    break;
            }
            break;
        case Tiling::HEXAGON:
            switch (heading) {
                case 0:
                    p += step;
                    r -= step;
                    break;
                case 1:
                    p += step;
                    q -= step;
                    break;
                case 2:
                    q -= step;
                    r += step;
                    break;
                case 3:
                    p -= step;
                    r += step;
                    break;
                case 4:
                    p -= step;
                    q += step;
                    break;
                case 5:
                    q += step;
                    r -= step;
                    break;
            }
            break;
    }

    return location;
}







