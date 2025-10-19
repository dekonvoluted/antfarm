#pragma once

#include "grid.hpp"

using Heading = int;

class Ant
{
public:
    Ant(const Grid&, Location = {}, Heading = {});

    friend class Grid;

    Location location() const;
    Heading heading() const;

    Ant& move(int = 1);
    // grid.where(location, heading, step)
    // move(grid.where(...));
    // Adjust heading if not valid.
    Ant& turn(int = 0);
    // heading += steps; modulo directions;


    Ant& update();



private:
    Ant& go(Location);
    Ant& face(Heading);

    const Grid& m_grid;
    Location m_location;
    Heading m_heading;
};




    heading is an integer.




    I would typically want to write this,

    SquareGrid grid(rows=10, cols=20);
    Ant ant(grid=grid, Index(0, 0), NORTH);

    ant.update(); => query grid, change its location, change its direction



    Can't create an ant without a grid. Let's keep a reference.
    

