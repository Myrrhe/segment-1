#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP
#include "System.hpp"
#include <SFML/Graphics.hpp>

class RenderSystem final : public System
{
public:
    /** Default constructor */
    RenderSystem();
    /** Default destructor */
    ~RenderSystem() override;
    /** Copy constructor
     *  \param other Object to copy from
     */
    void render(sf::RenderTarget &target) const;
};

#endif // RENDERSYSTEM_HPP
