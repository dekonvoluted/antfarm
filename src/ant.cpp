#include "ant.hpp"

Ant::Ant(const Grid& grid, Location location, Heading heading) : m_grid(grid), m_location(location), m_heading(heading)
{
}


















Ant& Ant::move(int step)
{
    grid.move(*this);
}

Ant& Ant::turn(int step)
{
    const auto modulus = grid.directions();

    // Rotate by given step
    // Ensure heading is non-negative
    // Ensure heading is modulo directions
    m_heading += step;
    while (m_heading < 0) {
        m_heading += modulus;
    }
    m_heading %= modulus;

    return *this;
}
