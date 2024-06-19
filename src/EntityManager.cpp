#include "EntityManager.hpp"
#include <cassert>

// Queue of unused entity IDs
std::queue<Entity> EntityManager::m_availableEntities;

// Array of signatures where the index corresponds to the entity ID
std::array<Signature, Entity::MAX_ENTITIES> EntityManager::m_signatures;

// Total living entities - used to keep limits on how many exist
long unsigned int EntityManager::m_livingEntityCount;

Entity EntityManager::createEntity()
{
    assert(m_livingEntityCount < Entity::MAX_ENTITIES && "Too many entities in existence.");

    // Take an ID from the front of the queue
    Entity id = m_availableEntities.front();
    m_availableEntities.pop();
    ++m_livingEntityCount;

    return id;
}

void EntityManager::destroyEntity(Entity entity)
{
    assert(Entity::MAX_ENTITIES > entity && "Entity out of range.");

    // Invalidate the destroyed entity's signature
    m_signatures[entity.getId()].reset();

    // Put the destroyed ID at the back of the queue
    m_availableEntities.push(entity);
    --m_livingEntityCount;
}

void EntityManager::setSignature(Entity entity, Signature signature)
{
    assert(Entity::MAX_ENTITIES > entity && "Entity out of range.");

    // Put this entity's signature into the array
    m_signatures[entity.getId()] = signature;
}

Signature EntityManager::getSignature(Entity entity)
{
    assert(Entity::MAX_ENTITIES > entity && "Entity out of range.");

    // Get this entity's signature from the array
    return m_signatures[entity.getId()];
}

void EntityManager::initialize()
{
    // Initialize the queue with all possible entity IDs
    for (auto entity = Entity(0); Entity::MAX_ENTITIES > entity; ++entity)
    {
        m_availableEntities.push(entity);
    }
}
