#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <functional>
#include <unordered_set>

class Entity final
{
public:
    /** Default constructor */
    Entity();
    /** Copy constructor
     *  \param other Object to copy from
     */

    explicit Entity(long unsigned int id);

    /** Default destructor */
    ~Entity();

    friend bool operator==(long unsigned int left, const Entity &right);
    friend bool operator!=(long unsigned int left, const Entity &right);
    friend bool operator<(long unsigned int left, const Entity &right);
    friend bool operator<=(long unsigned int left, const Entity &right);
    friend bool operator>(long unsigned int left, const Entity &right);
    friend bool operator>=(long unsigned int left, const Entity &right);

    friend bool operator==(const Entity &left, const Entity &right);
    friend bool operator<(const Entity &left, const Entity &right);

    Entity &operator++();
    Entity operator++(int);

    long unsigned int getId() const;

    static const long unsigned int MAX_ENTITIES = 5000;

private:
    long unsigned int m_id;
};

struct cus_hash
{
    std::size_t operator()(Entity const& entity) const noexcept
    {
        return std::hash<long unsigned int>{}(entity.getId());
    }
};

namespace std
{
    template <>
    struct hash<Entity>
    {
        std::size_t operator()(Entity const &entity) const noexcept
        {
            return std::hash<long unsigned int>{}(entity.getId());
        }
    };
}

#endif // ENTITY_HPP
