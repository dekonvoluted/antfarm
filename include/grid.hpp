#pragma once

#include <tuple>
#include <unordered_set>
#include <vector>

#include "ant.hpp"
#include "tiling.hpp"

class Grid {
public:
    // Create grid with tiling type and number of colors
    Grid(const Tiling, int = 2);

    // Return number of directions and colors
    int directions() const;
    int colors() const;
    std::vector<std::unordered_set<Location, LocationHash>> tiles();

    // Return color at a given location
    int color(Location) const;

    // Provide ways to validate location and heading
    bool valid(Location) const;
    bool valid(Heading, Location) const;

    // Provide way to calculate next tile
    Location next(Location, Heading, int) const;

    // Toggle color at given location
    Grid& toggle(Location);

    // Create an ant at location, with heading
    Grid& ant(Location = {}, Heading = {});

    // Update grid and ants
    Grid& update();

private:
    // Relocate and reorient an ant
    Grid& relocate(Ant&, Location);
    Grid& reorient(Ant&, Heading);

    const Tiling m_tiling;
    const int m_colors;
    std::vector<std::unordered_set<Location, LocationHash>> m_tiles;
    std::vector<Ant> m_ants {};
};
