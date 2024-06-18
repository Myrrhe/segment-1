#include "Components/Renderable.hpp"

Renderable::Renderable() : Component()
{
}

Renderable::~Renderable() = default;

Renderable::Renderable(std::size_t vertexCount, const sf::Color &color) : Component(),
                                                                          m_vertices(std::vector<sf::Vertex>(vertexCount, sf::Vertex(sf::Vector2<float>(0.0f, 0.0f), color))),
                                                                          m_vertexCount(vertexCount),
                                                                          m_type(sf::PrimitiveType::TriangleFan)
{
}

Renderable::Renderable(const Renderable &other) = default;

Renderable &Renderable::operator=(const Renderable &rhs)
{
    if (this == &rhs)
    {
        return *this; // handle self assignment
    }
    m_vertices = rhs.m_vertices;
    m_vertexCount = rhs.m_vertexCount;
    m_type = rhs.m_type;
    m_states = rhs.m_states;
    m_typeDraw = rhs.m_typeDraw;
    return *this;
}

void Renderable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.transform *= m_states.transform;
    if (states.texture == nullptr)
    {
        states.texture = m_states.texture;
    }
    if (states.shader == nullptr)
    {
        states.shader = m_states.shader;
    }
    target.draw(m_vertices.data(), m_vertexCount, m_type, states);
}

Renderable::TypeObjDraw Renderable::getTypeDraw() const
{
    return m_typeDraw;
}

std::size_t Renderable::getVertexCount() const
{
    return m_vertexCount;
}

void Renderable::setPositionVertex(std::size_t index, sf::Vector2<float> position)
{
    m_vertices[index].position = position;
}
