#ifndef SIGNATURE_HPP
#define SIGNATURE_HPP
#include "ComponentType.hpp"
#include <bitset>

class Signature final
{
public:
    /** Default constructor */
    Signature();
    /** Copy constructor
     *  \param other Object to copy from
     */

    explicit Signature(const std::bitset<static_cast<long unsigned int>(ComponentType::Type::MAX_COMPONENTS)> &bits);

    /** Default destructor */
    ~Signature();

    friend bool operator==(const Signature &left, const Signature &right);

    friend Signature operator&(const Signature &left, const Signature &right);

    void set(std::size_t pos, bool val);
    void set(const ComponentType &pos, bool val);

    void reset();

private:
    std::bitset<static_cast<long unsigned int>(ComponentType::Type::MAX_COMPONENTS)> m_bits;
};

#endif // SIGNATURE_HPP
