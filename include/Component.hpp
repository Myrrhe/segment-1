#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class Component
{
public:
    Component();
    /** Copy constructor
     *  \param other Object to copy from
     */
    Component(const Component &other);
    /** Default destructor */
    virtual ~Component();
    /** Assignment operator
     *  \param rhs Object to assign from
     *  \return A reference to this
     */
    Component &operator=(const Component &rhs) = delete;
};

#endif // COMPONENT_HPP
