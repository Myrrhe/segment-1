#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP
#include "Entity.hpp"
#include "Signature.hpp"
#include "StaticObject.hpp"
#include <array>
#include <queue>

class EntityManager final : private StaticObject
{
public:
    static Entity createEntity();

    static void destroyEntity(Entity entity);

    static void setSignature(Entity entity, Signature signature);

    static Signature getSignature(Entity entity);

    static void initialize();

private:
    // Queue of unused entity IDs
    static std::queue<Entity> m_availableEntities;

    // Array of signatures where the index corresponds to the entity ID
    static std::array<Signature, Entity::MAX_ENTITIES> m_signatures;

    // Total living entities - used to keep limits on how many exist
    static long unsigned int m_livingEntityCount;
};

#endif // ENTITYMANAGER_HPP
