#pragma once

#include <cstddef>
#include <functional>
#ifndef NDEBUG
#include <iostream>
#endif
#include <tuple>

using Location = std::tuple<int, int, int>;

// Needed to put the tuple into an unordered set later
struct LocationHash {
    std::size_t operator()(const Location& location) const
    {
        const auto [p, q, r] = location;

        const auto phash = std::hash<int> {}(p);
        const auto qhash = std::hash<int> {}(q);
        const auto rhash = std::hash<int> {}(r);

        return phash ^ (qhash << 1) ^ (rhash << 2);
    }
};

#ifndef NDEBUG
std::ostream& operator<<(std::ostream&, Location);
#endif
