#include "Coordinator.hpp"
#include "Components/Renderable.hpp"
#include "Systems/GraphicsSystem.hpp"
#include <iostream>
#include <istream>

GraphicsSystem::GraphicsSystem() : System()
{
    // ctor
}

GraphicsSystem::~GraphicsSystem() = default;

void GraphicsSystem::update() const
{
    std::for_each(m_entities.begin(), m_entities.end(), [](Entity entity) {
        Renderable const &renderable = Coordinator::getComponent<Renderable>(entity);
        if (renderable.getTypeDraw() == Renderable::TypeObjDraw::CIRCLE) {
            // Empty
        } else {
            // Empty
        }
    });
}
