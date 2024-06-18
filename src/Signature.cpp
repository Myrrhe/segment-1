#include "Signature.hpp"

Signature::Signature() : m_bits(0)
{
    // ctor
}

Signature::~Signature() = default;

Signature::Signature(const std::bitset<static_cast<long unsigned int>(ComponentType::Type::MAX_COMPONENTS)> &bits) : m_bits(bits)
{
}

void Signature::set(std::size_t pos, bool val)
{
    m_bits.set(pos, val);
}

void Signature::set(const ComponentType &pos, bool val)
{
    ComponentType::Type type = pos.getType();
    m_bits.set(static_cast<std::size_t>(type), val);
}

void Signature::reset()
{
    m_bits.reset();
}

bool operator==(const Signature &left, const Signature &right)
{
    return left.m_bits == right.m_bits;
}

Signature operator&(const Signature &left, const Signature &right)
{
    return Signature(left.m_bits & right.m_bits);
}
