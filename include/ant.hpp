#pragma once

#include "heading.hpp"
#include "location.hpp"

class Grid;

class Ant
{
public:
    Ant(Grid&, Location = {}, Heading = {});

    friend class Grid;

    Location location() const;
    Heading heading() const;

    // Basic operations for movement
    Ant& advance(int = 0);
    Ant& turn(int = 0);

    // Rules for this automaton
    Ant& update();

private:
    // Guarded operations
    Ant& move(Location);
    Ant& face(Heading);

    Grid& m_grid;
    Location m_location {};
    Heading m_heading {};
};

