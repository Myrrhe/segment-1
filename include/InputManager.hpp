#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP
#include "Input.hpp"
#include "StaticObject.hpp"

class InputManager final : private StaticObject
{
public:
    static void initialize();

    static void resetInput();

    static void getInput();

    static void update();

    static bool getQEntered();
    static bool getLeftEntered();
    static bool getRightEntered();
    static long unsigned int getArrowThicker();

    static bool isInsertMode();

    static bool isFirstFrameMouseClicked();
    static const sf::Vector2<int> &getFirstPosMouseClicked();

    static bool isInput(const std::string_view &str);
    static bool isInputPressed();
    static Input getInputPressed();
    static std::vector<Input> getAllInputPressed();
    static long unsigned int getNumberInputPressed();
    static bool getFirstInputPressed();
    static void setFirstInputPressed();

    static const std::array<std::string, sf::Joystick::AxisCount> strAxis;

private:
    static bool qEntered;
    static bool leftEntered;
    static bool rightEntered;

    static long unsigned int arrowThicker;

    static bool firstInputEntered;

    static bool insertMode;

    static bool mouseClicked;
    static bool firstFrameMouseClicked;
    static sf::Vector2<int> firstPosMouseClicked;
};

#endif // INPUTMANAGER_HPP
