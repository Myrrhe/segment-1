#include "Coordinator.hpp"
#include "Engine.hpp"
#include "InputManager.hpp"
#include "Components/Renderable.hpp"
#include "WindowManager.hpp"
#include <cmath>
#include <istream>

std::vector<Entity> Engine::entities;

GraphicsSystem *Engine::graphicsSystem;
RenderSystem *Engine::renderSystem;

bool Engine::firstIter;
long unsigned int Engine::frameCount;

void Engine::initialize()
{
    SystemManager::reserveSystems(100);
    ComponentManager::reserveComponentArrays(100);

    Coordinator::initialize();
    Coordinator::registerComponent<Renderable>();

    graphicsSystem = Coordinator::registerSystem<GraphicsSystem>();
    renderSystem = Coordinator::registerSystem<RenderSystem>();
    Signature signature;
    signature.set(Coordinator::getComponentType<Renderable>(), true);
    entities.resize(1);
    entities[0] = Coordinator::createEntity();
    Coordinator::addComponent(entities[0], Renderable(30, sf::Color(255, 0, 0)));

    graphicsSystem->update();

    firstIter = true;
    frameCount = 0;
}

void Engine::terminate()
{
    // Nothing to delete
}

void Engine::launch()
{
    initialize();
    while (WindowManager::isOpen())
    {
        getInput();
        update();
        draw(*WindowManager::getRenderWindow());
        WindowManager::display();
    }
    terminate();
}

void Engine::getInput()
{
    InputManager::resetInput();
    if (WindowManager::hasFocus())
    {
        InputManager::getInput();
    }
}

void Engine::update()
{
    WindowManager::manageEvent();
    InputManager::update();

    ++frameCount;
    if (InputManager::getQEntered())
    {
        WindowManager::close();
    }
    if (firstIter)
    {
        firstIter = false;
    }
}

void Engine::draw(sf::RenderTarget &renderTarget)
{
    renderTarget.clear(sf::Color(0, 0, 0, 255));

    renderSystem->render(renderTarget);
}
