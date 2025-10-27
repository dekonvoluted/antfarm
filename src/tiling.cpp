#include <stdexcept>

#include "tiling.hpp"

template <>
bool valid<Tiling::TRIANGLE>(Location location)
{
    const auto [p, q, r] = location;
    return r == 0 or r == 1;
}

template <>
bool valid<Tiling::SQUARE>(Location location)
{
    // Square grids disregard the third coordinate
    const auto [p, q, r] = location;
    return r == 0;
}

template <>
bool valid<Tiling::HEXAGON>(Location location)
{
    // Hexagon grids need to preserve an invariant
    const auto [p, q, r] = location;
    return p + q + r == 0;
}

bool valid(Heading heading, Location location)
{
    // Triangular tiling needs additional checks based on location
    // Left-pointing triangles have r = 0 and allow 0, 2, 4 headings
    // Right-pointing triangles have r = 1 and allow 1, 3, 5 headings
    const auto [p, q, r] = location;
    return (heading % 2) == r;
}

template <>
Location next<Tiling::TRIANGLE>(Location location, Heading heading, int step)
{
    auto& [p, q, r] = location;

    // Disallow multiple steps
    if (step < -1 or step > 1) {
        throw std::runtime_error("Multiple steps are ambiguous on a triangle tiling");
    }

    // Toggle left-/right-pointedness
    if (step) {
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

    // NOTE - Heading may no longer be valid at new location
    return location;
}

template <>
Location next<Tiling::SQUARE>(Location location, Heading heading, int step)
{
    auto& [p, q, r] = location;

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

    return location;
}

template <>
Location next<Tiling::HEXAGON>(Location location, Heading heading, int step)
{
    auto& [p, q, r] = location;

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

    return location;
}
