#include "Coordinator.hpp"

void Coordinator::initialize()
{
    // Create pointers to each manager
    EntityManager::initialize();
}

// Entity methods
Entity Coordinator::createEntity()
{
    return EntityManager::createEntity();
}

void Coordinator::destroyEntity(Entity entity)
{
    EntityManager::destroyEntity(entity);
    ComponentManager::entityDestroyed(entity);
    SystemManager::entityDestroyed(entity);
}
