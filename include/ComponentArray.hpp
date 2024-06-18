#ifndef COMPONENTARRAY_HPP
#define COMPONENTARRAY_HPP
#include "IComponentArray.hpp"
#include <array>
#include <cassert>
#include <unordered_map>

template <typename T>
class ComponentArray final : public IComponentArray
{
public:
    /** Default constructor */
    ComponentArray() : IComponentArray()
    {
        //ctor
    }
    /** Default destructor */
    ~ComponentArray() override = default;
    /** Copy constructor
     *  \param other Object to copy from
     */
    ComponentArray(const ComponentArray &other) = delete;
    ComponentArray &operator=(const ComponentArray &rhs) = delete;

    void insertData(Entity entity, T component)
    {
        assert(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end() && "Component added to same entity more than once.");

        // Put new entry at end and update the maps
        std::size_t newIndex = m_size;
        m_entityToIndexMap[entity] = newIndex;
        m_indexToEntityMap[newIndex] = entity;
        m_componentArray[newIndex] = component;
        ++m_size;
    }

    void removeData(Entity entity)
    {
        assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Removing non-existent component.");

        // Copy element at end into deleted element's place to maintain density
        std::size_t indexOfRemovedEntity = m_entityToIndexMap[entity];
        std::size_t indexOfLastElement = m_size - 1;
        m_componentArray[indexOfRemovedEntity] = m_componentArray[indexOfLastElement];

        // Update map to point to moved spot
        Entity entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
        m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        m_entityToIndexMap.erase(entity);
        m_indexToEntityMap.erase(indexOfLastElement);

        --m_size;
    }

    T &getData(Entity entity)
    {
        assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Retrieving non-existent component.");

        // Return a reference to the entity's component
        return m_componentArray[m_entityToIndexMap[entity]];
    }

    void entityDestroyed(Entity entity) override
    {
        if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
        {
            // Remove the entity's component if it existed
            removeData(entity);
        }
    }

private:
    // The packed array of components (of generic type T),
    // set to a specified maximum amount, matching the maximum number
    // of entities allowed to exist simultaneously, so that each entity
    // has a unique spot.
    std::array<T, Entity::MAX_ENTITIES> m_componentArray;

    // Map from an entity ID to an array index.
    std::unordered_map<Entity, std::size_t> m_entityToIndexMap;

    // Map from an array index to an entity ID.
    std::unordered_map<std::size_t, Entity> m_indexToEntityMap;

    // Total size of valid entries in the array.
    std::size_t m_size = 0;
};

#endif // COMPONENTARRAY_HPP
