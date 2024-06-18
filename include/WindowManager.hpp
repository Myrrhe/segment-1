#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <array>
#include <stack>
#include <string>
#include <vector>
#include "StaticObject.hpp"

class WindowManager final : private StaticObject
{
public:
    enum class IdView : long unsigned int
    {
        MAIN,
        UI,
        SHAKE,
        WHOLE
    };

    static void getMonitorSize();

    static void create();
    static void initialize();
    static void terminate();

    static void pushStateView(IdView idView);
    static void popStateView();
    static void setViewTarget(sf::RenderTarget &renderTarget);

    static void setUiView(float x, float y, float widthUi, float heightUi);

    static void setOffsetX(float newOffsetX);
    static void setOffsetY(float newOffsetY);

    static void manageEvent();

    static bool isOpen();
    static bool pollEvent(sf::Event &event);
    static bool hasFocus();
    static void close();
    static void clear(const sf::Color &color = sf::Color(0, 0, 0, 255));
    static void draw(const sf::Vertex *vertices, std::size_t vertexCount, sf::PrimitiveType type, const sf::RenderStates &states = sf::RenderStates::Default);
    static void draw(const sf::Drawable &drawable, const sf::RenderStates &states = sf::RenderStates::Default);
    static void display();
    static sf::Vector2<int> getMousePosition();
    static sf::Vector2<float> mapPixelToCoords(const sf::Vector2<int> &point);

    static sf::RenderWindow *getRenderWindow();

    static bool isTextEntered();
    static char32_t getCharEntered();

    static bool isKeyPressed();
    static sf::Keyboard::Key getKeyPressed();

    static bool isAltEntered();
    static bool isControlEntered();
    static bool isShiftEntered();
    static bool isSystemEntered();

    static const long unsigned int Width;
    static const long unsigned int Height;

    static const bool Fullscreen;

private:
    static sf::RenderWindow *renderWindow;
    static sf::Texture *textureIcon;

    static std::array<sf::View, 4> views;
    static std::stack<IdView> stateView;

    static float mainScale;

    static float uiX;
    static float uiY;
    static float uiWidth;
    static float uiHeight;

    static float offsetX;
    static float offsetY;

    static sf::Vector2<unsigned int> monitorSize;

    static bool textEntered;
    static char32_t charEntered;

    static bool keyPressed;
    static sf::Keyboard::Key codeKeyPressed;

    static bool altEntered;
    static bool controlEntered;
    static bool shiftEntered;
    static bool systemEntered;
};

#endif // WINDOWMANAGER_HPP
