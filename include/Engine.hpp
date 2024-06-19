#ifndef ENGINE_HPP
#define ENGINE_HPP
#include "Systems/GraphicsSystem.hpp"
#include "Systems/RenderSystem.hpp"
#include "StaticObject.hpp"
#include <SFML/Graphics.hpp>

class Engine final : private StaticObject
{
public:
    static void launch();

private:
    static void initialize();
    static void terminate();

    static void getInput();
    static void update();
    static void draw(sf::RenderTarget &renderTarget);

    static std::vector<Entity> entities;

    static GraphicsSystem *graphicsSystem;
    static RenderSystem *renderSystem;

    static bool firstIter;
    static long unsigned int frameCount;
};

#endif // ENGINE_HPP
