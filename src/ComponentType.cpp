#include "ComponentType.hpp"

ComponentType::ComponentType() = default;

ComponentType::~ComponentType() = default;

ComponentType::ComponentType(const Type &type) : m_type(type)
{
}

ComponentType::ComponentType(long unsigned int type) : m_type(static_cast<Type>(type))
{
}

ComponentType &ComponentType::operator++()
{
    m_type = static_cast<Type>(static_cast<long unsigned int>(m_type) + 1);
    return *this;
}

ComponentType ComponentType::operator++(int)
{
    ComponentType res = *this;
    m_type = static_cast<Type>(static_cast<long unsigned int>(m_type) + 1);
    return res;
}

ComponentType::Type ComponentType::getType() const
{
    return m_type;
}
