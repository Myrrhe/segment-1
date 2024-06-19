#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include "Entity.hpp"
#include <set>

class System
{
public:
    /** Default constructor */
    System();
    /** Default destructor */
    virtual ~System();
    /** Copy constructor
     *  \param other Object to copy from
     */
    System(const System &other) = delete;
    /** Assignment operator
     *  \param rhs Object to assign from
     *  \return A reference to this
     */
    System &operator=(const System &rhs) = delete;

    template <typename T>
    static void allocate(std::size_t n) {
        T::m_systems.reserve(n);
    }

    std::set<Entity> m_entities;
};

#endif // SYSTEM_HPP
