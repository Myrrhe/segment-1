#ifndef COMPONENTTYPE_HPP
#define COMPONENTTYPE_HPP

class ComponentType final
{
public:
    enum class Type : long unsigned int
    {
        RENDERABLE,
        MAX_COMPONENTS,
    };

    /** Default constructor */
    ComponentType();
    /** Default destructor */
    ~ComponentType();

    explicit ComponentType(const Type &type);

    explicit ComponentType(long unsigned int type);

    ComponentType &operator++();
    ComponentType operator++(int);

    Type getType() const;

private:
    Type m_type;
};

#endif // COMPONENTTYPE_HPP
