#include "location.hpp"

#ifndef NDEBUG
std::ostream& operator<<(std::ostream& stream, Location location)
{
    stream << "(" << std::get<0>(location) << ", " << std::get<1>(location) << ", " << std::get<2>(location) << ")";
    return stream;
}
#endif
