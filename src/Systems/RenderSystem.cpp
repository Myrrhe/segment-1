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
    std::for_each(m_entities.begin(), m_entities.end(), [&target](Entity entity) {
        target.draw(Coordinator::getComponent<Renderable>(entity));
    });
}
