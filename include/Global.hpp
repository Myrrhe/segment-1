#ifndef GLOBAL_HPP
#define GLOBAL_HPP
#include "StaticObject.hpp"

constexpr bool DEBUG = true;

class Global final : private StaticObject
{

};

#endif // GLOBAL_HPP
