#ifndef ICOMPONENTARRAY_HPP
#define ICOMPONENTARRAY_HPP
#include "Entity.hpp"

class IComponentArray
{
public:
    /** Default constructor */
    IComponentArray();
    /** Default destructor */
    virtual ~IComponentArray();
    /** Copy constructor
     *  \param other Object to copy from
     */
    IComponentArray(const IComponentArray & /*other*/) = default;
    /** Assignment operator
     *  \param other Object to assign from
     *  \return A reference to this
     */
    IComponentArray &operator=(const IComponentArray &other) = default;

    virtual void entityDestroyed(Entity entity) = 0;
};

#endif // ICOMPONENTARRAY_HPP
