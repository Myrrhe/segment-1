#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "StaticObject.hpp"
#include "SystemManager.hpp"
#include <memory>

class Coordinator : private StaticObject
{
public:
    static void initialize();

    static Entity createEntity();

    static void destroyEntity(Entity entity);

    // Component methods
    template <typename T>
    static void registerComponent()
    {
        ComponentManager::registerComponent<T>();
    }

    template <typename T>
    static void addComponent(Entity entity, T component)
    {
        ComponentManager::addComponent<T>(entity, component);

        Signature signature = EntityManager::getSignature(entity);
        signature.set(ComponentManager::getComponentType<T>(), true);
        EntityManager::setSignature(entity, signature);

        SystemManager::entitySignatureChanged(entity, signature);
    }

    template <typename T>
    static void removeComponent(Entity entity)
    {
        ComponentManager::removeComponent<T>(entity);

        Signature signature = EntityManager::getSignature(entity);
        signature.set(ComponentManager::getComponentType<T>(), false);
        EntityManager::setSignature(entity, signature);

        SystemManager::entitySignatureChanged(entity, signature);
    }

    template <typename T>
    static T &getComponent(Entity entity)
    {
        return ComponentManager::getComponent<T>(entity);
    }

    template <typename T>
    static ComponentType getComponentType()
    {
        return ComponentManager::getComponentType<T>();
    }

    // System methods
    template <typename T>
    static T *registerSystem()
    {
        return SystemManager::registerSystem<T>();
    }

    template <typename T>
    static void setSystemSignature(Signature signature)
    {
        SystemManager::setSignature<T>(signature);
    }
};

#endif // COORDINATOR_HPP
