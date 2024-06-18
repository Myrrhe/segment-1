/*
 * The file that manage the main window.
 * Copyright (C) 2020  Myrrhe <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "MouseWheel.hpp"
#include "OsManager.hpp"
#include "PathManager.hpp"
#include "WindowManager.hpp"
#include <iostream>
#include <istream>

sf::RenderWindow *WindowManager::renderWindow;
sf::Texture *WindowManager::textureIcon;

std::array<sf::View, 4> WindowManager::views;
std::stack<WindowManager::IdView> WindowManager::stateView;

float WindowManager::mainScale;

float WindowManager::uiX;
float WindowManager::uiY;
float WindowManager::uiWidth;
float WindowManager::uiHeight;

float WindowManager::offsetX;
float WindowManager::offsetY;

sf::Vector2<unsigned int> WindowManager::monitorSize;

bool WindowManager::textEntered;
char32_t WindowManager::charEntered;

bool WindowManager::keyPressed;
sf::Keyboard::Key WindowManager::codeKeyPressed;

bool WindowManager::altEntered;
bool WindowManager::controlEntered;
bool WindowManager::shiftEntered;
bool WindowManager::systemEntered;

const long unsigned int WindowManager::Width = 600;
const long unsigned int WindowManager::Height = 600;

const bool WindowManager::Fullscreen = false;

void WindowManager::getMonitorSize()
{
    monitorSize = OsManager::getMonitorSize();
}

void WindowManager::create()
{
    (renderWindow = new sf::RenderWindow)->create(sf::VideoMode(Width, Height, 32u), "", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(0, 0, 0, 1u, 1u, sf::ContextSettings::Attribute::Default, false));
    stateView.push(IdView::MAIN);
    setViewTarget(*renderWindow);
}

void WindowManager::initialize()
{
    renderWindow->setTitle("Watch");
    renderWindow->setVerticalSyncEnabled(false);
    renderWindow->setMouseCursorVisible(true);
    renderWindow->setMouseCursorGrabbed(false);
    renderWindow->setFramerateLimit(60);

    textEntered = false;
    charEntered = 0;

    keyPressed = false;
    codeKeyPressed = sf::Keyboard::Key::A;

    altEntered = false;
    controlEntered = false;
    shiftEntered = false;
    systemEntered = false;
}

void WindowManager::terminate()
{
    delete renderWindow;
}

void WindowManager::pushStateView(IdView idView)
{
    stateView.push(idView);
}

void WindowManager::popStateView()
{
    stateView.pop();
}

void WindowManager::setViewTarget(sf::RenderTarget &renderTarget)
{
    sf::Vector2<unsigned int> sizeTarget = renderTarget.getSize();
    switch (stateView.top())
    {
    case IdView::MAIN:
    {
        mainScale = std::min(static_cast<float>(sizeTarget.x) / static_cast<float>(Width), static_cast<float>(sizeTarget.y) / static_cast<float>(Height));
        auto rendingSizeX = static_cast<float>(Fullscreen ? monitorSize.x : sizeTarget.x);
        auto rendingSizeY = static_cast<float>(Fullscreen ? monitorSize.y : sizeTarget.y);
        views[0].reset(sf::Rect<float>(0.0f, 0.0f, Width, Height));
        views[0].setViewport(sf::Rect<float>((rendingSizeX - Width * mainScale) * 0.5f / rendingSizeX,
                                             (rendingSizeY - Height * mainScale) * 0.5f / rendingSizeY,
                                             1.0f - 2.0f * (rendingSizeX - Width * mainScale) * 0.5f / rendingSizeX,
                                             1.0f - 2.0f * (rendingSizeY - Height * mainScale) * 0.5f / rendingSizeY));
        renderTarget.setView(views[0]);
        break;
    }
    case IdView::UI:
    {
        auto rendingSizeX = static_cast<float>(Fullscreen ? monitorSize.x : sizeTarget.x);
        auto rendingSizeY = static_cast<float>(Fullscreen ? monitorSize.y : sizeTarget.y);
        views[1].reset(sf::Rect<float>(uiX, uiY, uiWidth, uiHeight));
        views[1].setViewport(sf::Rect<float>(((rendingSizeX - Width * mainScale) * 0.5f + uiX * mainScale) / rendingSizeX,
                                             ((rendingSizeY - Height * mainScale) * 0.5f + uiY * mainScale) / rendingSizeY,
                                             uiWidth * mainScale / rendingSizeX,
                                             uiHeight * mainScale / rendingSizeY));
        renderTarget.setView(views[1]);
        break;
    }
    case IdView::SHAKE:
    {
        mainScale = std::min(static_cast<float>(sizeTarget.x) / static_cast<float>(Width), static_cast<float>(sizeTarget.y) / static_cast<float>(Height));
        auto rendingSizeX = static_cast<float>(Fullscreen ? monitorSize.x : sizeTarget.x);
        auto rendingSizeY = static_cast<float>(Fullscreen ? monitorSize.y : sizeTarget.y);
        views[2].reset(sf::Rect<float>(0.0f, 0.0f, Width, Height));
        views[2].setViewport(sf::Rect<float>((rendingSizeX - (Width + 2.0f * offsetX) * mainScale) * 0.5f / rendingSizeX,
                                             (rendingSizeY - (Height + 2.0f * offsetY) * mainScale) * 0.5f / rendingSizeY,
                                             1.0f - 2.0f * (rendingSizeX - Width * mainScale) * 0.5f / rendingSizeX,
                                             1.0f - 2.0f * (rendingSizeY - Height * mainScale) * 0.5f / rendingSizeY));
        renderTarget.setView(views[2]);
        break;
    }
    case IdView::WHOLE:
    {
        views[3].reset(sf::Rect<float>(0.0f, 0.0f, Width, Height));
        views[3].setViewport(sf::Rect<float>(0.0f, 0.0f, 1.0f, 1.0f));
        renderTarget.setView(views[3]);
        break;
    }
    default:
    {
        break;
    }
    }
}

void WindowManager::setUiView(float x, float y, float widthUi, float heightUi)
{
    uiX = x;
    uiY = y;
    uiWidth = widthUi;
    uiHeight = heightUi;
}

void WindowManager::setOffsetX(float newOffsetX)
{
    offsetX = newOffsetX;
}

void WindowManager::setOffsetY(float newOffsetY)
{
    offsetY = newOffsetY;
}

void WindowManager::manageEvent()
{
    MouseWheel::setDeltaWheel(0);
    sf::Event event;
    textEntered = false;
    keyPressed = false;
    while (renderWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            renderWindow->close();
        }
        else if (event.type == sf::Event::MouseWheelMoved)
        {
            MouseWheel::setDeltaWheel(event.mouseWheel.delta);
        }
        else if (event.type == sf::Event::TextEntered)
        {
            textEntered = true;
            charEntered = event.text.unicode;
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            keyPressed = true;
            codeKeyPressed = event.key.code;
            altEntered = event.key.alt;
            controlEntered = event.key.control;
            shiftEntered = event.key.shift;
            systemEntered = event.key.system;
        }
    }
}

bool WindowManager::isOpen()
{
    return renderWindow->isOpen();
}

bool WindowManager::pollEvent(sf::Event &event)
{
    return renderWindow->pollEvent(event);
}

bool WindowManager::hasFocus()
{
    return renderWindow->hasFocus();
}

void WindowManager::close()
{
    renderWindow->close();
}

void WindowManager::clear(const sf::Color &color)
{
    renderWindow->clear(color);
}

void WindowManager::draw(const sf::Vertex *vertices, std::size_t vertexCount, sf::PrimitiveType type, const sf::RenderStates &states)
{
    renderWindow->draw(vertices, vertexCount, type, states);
}

void WindowManager::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
{
    renderWindow->draw(drawable, states);
}

void WindowManager::display()
{
    renderWindow->display();
}

sf::Vector2<int> WindowManager::getMousePosition()
{
    return sf::Mouse::getPosition(*renderWindow);
}

sf::Vector2<float> WindowManager::mapPixelToCoords(const sf::Vector2<int> &point)
{
    return renderWindow->mapPixelToCoords(point);
}

sf::RenderWindow *WindowManager::getRenderWindow()
{
    return renderWindow;
}

bool WindowManager::isTextEntered()
{
    return textEntered;
}

char32_t WindowManager::getCharEntered()
{
    return charEntered;
}

bool WindowManager::isKeyPressed()
{
    return keyPressed;
}

sf::Keyboard::Key WindowManager::getKeyPressed()
{
    return codeKeyPressed;
}

bool WindowManager::isAltEntered()
{
    return altEntered;
}

bool WindowManager::isControlEntered()
{
    return controlEntered;
}

bool WindowManager::isShiftEntered()
{
    return shiftEntered;
}

bool WindowManager::isSystemEntered()
{
    return systemEntered;
}
