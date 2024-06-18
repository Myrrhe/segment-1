#include "ComponentManager.hpp"

// Map from type string pointer to a component type
std::unordered_map<const char *, ComponentType> ComponentManager::m_componentTypes;

// Map from type string pointer to a component array
std::unordered_map<const char *, IComponentArray *> ComponentManager::m_componentArrays;

// The component type to be assigned to the next registered component - starting at 0
ComponentType ComponentManager::m_nextComponentType;

void ComponentManager::entityDestroyed(Entity entity)
{
    // Notify each component array that an entity has been destroyed
    // If it has a component for that entity, it will remove it
    // for (std::unordered_map<const char *, IComponentArray *>::iterator it = m_componentArrays.begin(); it != m_componentArrays.end(); it++)
    // {
    //     it->second->entityDestroyed(entity);
    // }

    std::for_each(m_componentArrays.begin(), m_componentArrays.end(), [&entity](std::pair<const char *, IComponentArray *> element) {
        element.second->entityDestroyed(entity);
    });
}

void ComponentManager::reserveComponentArrays(long unsigned int sizeReserve)
{
    m_componentArrays.reserve(sizeReserve);
}
