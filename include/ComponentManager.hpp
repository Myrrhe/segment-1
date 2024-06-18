#ifndef COMPONENTMANAGER_HPP
#define COMPONENTMANAGER_HPP
#include "ComponentType.hpp"
#include "ComponentArray.hpp"
#include "StaticObject.hpp"
#include <cassert>
#include <memory>
#include <unordered_map>

class ComponentManager final : private StaticObject
{
public:
    template <typename T>
    static void registerComponent()
    {
        const char *typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) == m_componentTypes.end() && "Registering component type more than once.");

        // Add this component type to the component type map
        m_componentTypes.insert({{typeName, m_nextComponentType}});

        // Create a ComponentArray pointer and add it to the component arrays map
        m_componentArrays[typeName] = new ComponentArray<T>;

        // Increment the value so that the next component registered will be different
        ++m_nextComponentType;
    }

    template <typename T>
    static ComponentType getComponentType()
    {
        const char *typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");

        // Return this component's type - used for creating signatures
        return m_componentTypes[typeName];
    }

    template <typename T>
    static void addComponent(Entity entity, T component)
    {
        // Add a component to the array for an entity
        getComponentArray<T>()->insertData(entity, component);
    }

    template <typename T>
    static void removeComponent(Entity entity)
    {
        // Remove a component from the array for an entity
        getComponentArray<T>()->removeData(entity);
    }

    template <typename T>
    static T &getComponent(Entity entity)
    {
        // Get a reference to a component from the array for an entity
        return getComponentArray<T>()->getData(entity);
    }

    static void entityDestroyed(Entity entity);

    static void reserveComponentArrays(long unsigned int sizeReserve);

private:
    // Map from type string pointer to a component type
    static std::unordered_map<const char *, ComponentType> m_componentTypes;

    // Map from type string pointer to a component array
    static std::unordered_map<const char *, IComponentArray *> m_componentArrays;

    // The component type to be assigned to the next registered component - starting at 0
    static ComponentType m_nextComponentType;

    template <typename T>
    static ComponentArray<T> *getComponentArray()
    {
        const char *typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");

        return dynamic_cast<ComponentArray<T> *>(m_componentArrays[typeName]);
    }
};

#endif // COMPONENTMANAGER_HPP
