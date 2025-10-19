#pragma once

#include <tuple>
#include <unordered_set>
#include <vector>

class Ant;

enum class Tiling {
    TRIANGLE,
    SQUARE,
    HEXAGON,
};

using Location = std::tuple<int, int, int>
using Heading = int;

class Grid
{
public:
    Grid(const Tiling, int = 2);

    int directions() const;
    int colors() const;
    int color(Location) const;

    bool valid(Location) const;
    bool valid(Heading, Location) const;

    Grid& toggle(Location);

    Grid& ant(Location = {}, Heading = {});

    Grid& update(); // Call ant.update() on each ant

private:
    Grid& place(Ant&, Location);
    Grid& point(Ant&, Heading);
    Location where(Location, Heading, int) const;

    const Tiling m_tiling
    const int m_directions;
    const int m_colors;

    std::vector<std::unordered_set<Location>> m_tiles;
    std::vector<Ant> m_ants {};
};


// Grid should be Farm
// Farm is created with tiling option
// Farm can be queried for number of directions
//   This is used as a modulus for heading
// Farm can create Ant objects
