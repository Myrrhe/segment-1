#include "SystemManager.hpp"

// Map from system type string pointer to a signature
std::unordered_map<const char *, Signature> SystemManager::m_signatures;

// Map from system type string pointer to a system pointer
std::unordered_map<const char *, System *> SystemManager::m_systems;

void SystemManager::entityDestroyed(Entity entity)
{
    // Erase a destroyed entity from all system lists
    // mEntities is a set so no check needed
    std::for_each(m_systems.begin(), m_systems.end(), [&entity](std::pair<const char *, System *> element) {
        element.second->m_entities.erase(entity);
    });
}

void SystemManager::entitySignatureChanged(Entity entity, Signature entitySignature)
{
    std::for_each(m_systems.begin(), m_systems.end(), [&entity, &entitySignature](std::pair<const char *, System *> element) {
        const char *type = element.first;
        System *system = element.second;
        const Signature systemSignature = m_signatures[type];

        // Entity signature matches system signature - insert into set
        if ((entitySignature & systemSignature) == systemSignature)
        {
            system->m_entities.insert(entity);
        }
        // Entity signature does not match system signature - erase from set
        else
        {
            system->m_entities.erase(entity);
        }
    });
}

void SystemManager::reserveSystems(long unsigned int sizeReserve)
{
    m_systems.reserve(sizeReserve);
}
