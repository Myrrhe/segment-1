#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP
#include "Signature.hpp"
#include "StaticObject.hpp"
#include "System.hpp"
#include <cassert>
#include <memory>
#include <unordered_map>

class SystemManager final : private StaticObject
{
public:
    template <typename T>
    static T *registerSystem()
    {
        const char *typeName = typeid(T).name();

        assert(m_systems.find(typeName) == m_systems.end() && "Registering system more than once.");

        // Create a pointer to the system and return it so it can be used externally
        // std::shared_ptr<T> system = std::make_shared<T>();
        // m_systems.insert({typeName, system});
        auto *system = new T;
        m_systems[typeName] = system;
        return system;
    }

    template <typename T>
    static void setSignature(Signature signature)
    {
        const char *typeName = typeid(T).name();

        assert(m_systems.find(typeName) != m_systems.end() && "System used before registered.");

        // Set the signature for this system
        m_signatures.insert({{typeName, signature}});
    }

    static void entityDestroyed(Entity entity);

    static void entitySignatureChanged(Entity entity, Signature entitySignature);

    static void reserveSystems(long unsigned int sizeReserve);

private:
    // Map from system type string pointer to a signature
    static std::unordered_map<const char *, Signature> m_signatures;

    // Map from system type string pointer to a system pointer
    static std::unordered_map<const char *, System *> m_systems;
};

#endif // SYSTEMMANAGER_HPP
