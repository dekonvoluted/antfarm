#pragma once

#include "heading.hpp"
#include "location.hpp"

enum class Tiling {
    TRIANGLE,
    SQUARE,
    HEXAGON
};

// Get maximum number of directions for a tiling
template <Tiling T>
constexpr int directions()
{
    // Triangle grids have six directions, but only three are allowed at a time
    // Hexagon grids have six directions, and all six are allowed at any time
    return 6;
}

// Check if a location is valid for a tiling
template <Tiling T>
bool valid(Location);

// Check if a heading is valid for a triangle tiling
bool valid(Heading, Location);

// Get the next tile location after taking steps
// Start with location and heading
template <Tiling T>
Location next(Location, Heading, int = 1);
