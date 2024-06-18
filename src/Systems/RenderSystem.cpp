#include "Coordinator.hpp"
#include "Components/Renderable.hpp"
#include "Systems/RenderSystem.hpp"

RenderSystem::RenderSystem() : System()
{
    // ctor
}

RenderSystem::~RenderSystem() = default;

void RenderSystem::render(sf::RenderTarget &target) const
{
    // for (std::set<Entity>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
    // {
    //     target.draw(Coordinator::getComponent<Renderable>(*it));
    // }
    std::for_each(m_entities.begin(), m_entities.end(), [&target](Entity entity) {
        target.draw(Coordinator::getComponent<Renderable>(entity));
    });
}
