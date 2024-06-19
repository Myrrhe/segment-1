#include "Entity.hpp"

Entity::Entity() : m_id(0)
{
    // ctor
}

Entity::~Entity() = default;

Entity::Entity(long unsigned int id) : m_id(id)
{
}

bool operator==(long unsigned int left, const Entity &right)
{
    return left == right.getId();
}

bool operator!=(long unsigned int left, const Entity &right)
{
    return left != right.getId();
}

bool operator<(long unsigned int left, const Entity &right)
{
    return left < right.getId();
}

bool operator<=(long unsigned int left, const Entity &right)
{
    return left <= right.getId();
}

bool operator>(long unsigned int left, const Entity &right)
{
    return left > right.getId();
}

bool operator>=(long unsigned int left, const Entity &right)
{
    return left >= right.getId();
}

bool operator==(const Entity &left, const Entity &right)
{
    return left.getId() == right.getId();
}

bool operator<(const Entity &left, const Entity &right)
{
    return left.getId() < right.getId();
}

Entity &Entity::operator++()
{
    ++m_id;
    return *this;
}

Entity Entity::operator++(int)
{
    return Entity(m_id++);
}

long unsigned int Entity::getId() const
{
    return m_id;
}
