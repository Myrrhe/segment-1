#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP
#include "Component.hpp"
#include <SFML/Graphics.hpp>

using float32_t = float;

class Renderable final : public Component,
                         public sf::Transformable,
                         public sf::Drawable
{
public:
    enum class TypeObjDraw : std::size_t
    {
        CIRCLE
    };

    /** Default constructor */
    Renderable();
    Renderable(std::size_t vertexCount, const sf::Color &color);
    /** Default destructor */
    ~Renderable() override;
    /** Copy constructor
     *  \param other Object to copy from
     */
    Renderable(const Renderable &other);
    /** Assignment operator
     *  \param other Object to assign from
     *  \return A reference to this
     */
    Renderable &operator=(const Renderable &other);

    void draw(
        sf::RenderTarget &target,
        sf::RenderStates states
    ) const override;

    TypeObjDraw getTypeDraw() const;

    std::size_t getVertexCount() const;

    void setPositionVertex(std::size_t index, sf::Vector2<float32_t> position);

private:
    std::vector<sf::Vertex> m_vertices = {};
    std::size_t m_vertexCount = 0;
    sf::PrimitiveType m_type = sf::PrimitiveType::Points;
    sf::RenderStates m_states = sf::RenderStates::Default;
    TypeObjDraw m_typeDraw = Renderable::TypeObjDraw::CIRCLE;
};

#endif // RENDERABLE_HPP
