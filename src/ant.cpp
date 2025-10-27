#include <stdexcept>

#include "ant.hpp"
#include "grid.hpp"

Ant::Ant(Grid& grid, Location location, Heading heading)
    : m_grid(grid)
{
    move(location);
    face(heading);
}

Location Ant::location() const
{
    return m_location;
}

Heading Ant::heading() const
{
    return m_heading;
}

Ant& Ant::advance(int steps)
{
    move(m_grid.next(m_location, m_heading, steps));

    // Adjust heading, if needed
    auto count = 0;
    while (not m_grid.valid(m_heading + count, m_location)) {
        ++count;
    }
    if (count) {
        turn(count);
    }

    return *this;
};

Ant& Ant::turn(int steps)
{
    face(m_heading + steps);

    return *this;
}

Ant& Ant::update()
{
    // Rules for this automaton
    // Toggle color, turn, advance
    m_grid.toggle(m_location);

    const auto color = m_grid.color(m_location);
    if (color == 0) {
        turn(-1);

    } else if (color == 1) {
        turn(1);
    }

    advance(1);

    return *this;
}

Ant& Ant::move(Location location)
{
    // Verify that the location is valid for this grid
    if (not m_grid.valid(location)) {
        throw std::runtime_error("Unable to move ant to invalid location");
    }

    m_location = location;

    return *this;
}

Ant& Ant::face(Heading heading)
{
    // Ensure heading is non-negative
    // Ensure heading is modulo grid directions
    const auto modulus = m_grid.directions();
    while (heading < 0) {
        heading += modulus;
    }
    heading %= modulus;

    // Verify that the heading is valid for this grid
    if (not m_grid.valid(heading, location())) {
        throw std::runtime_error("Unable to face ant to invalid heading");
    }

    m_heading = heading;

    return *this;
}
