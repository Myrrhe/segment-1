#include <SFML/Graphics.hpp>
#include "Engine.hpp"
#include "Input.hpp"
#include "InputManager.hpp"
#include "MouseWheel.hpp"
#include "OsManager.hpp"
#include "PathManager.hpp"
#include "WindowManager.hpp"

int main(int /*argc*/, char **argv, char ** /*options*/)
{
    WindowManager::create();
    OsManager::initiateCoreFile();
    PathManager::setPath(argv[0]);
    PathManager::initialize();
    WindowManager::getMonitorSize();
    WindowManager::initialize();
    MouseWheel::initialize();
    Input::initialize();
    InputManager::initialize();
    Engine::launch();
    WindowManager::terminate();
    return 0;
}
