#ifndef BUTTON
#define BUTTON

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

#include "element.h"

// class WindowControl;
// enum WindowControl::State : unsigned int;
#include "windowControl.h"

class Button : public Element {
    public:

        static const int STD_WIDTH;
        static const int STD_HEIGHT;
        static const int STD_TXT_SIZE;
        static const sf::Color STD_TXT_COLOR;
        static const sf::Color STD_BTN_COLOR;
        static const sf::Color STD_BTN_HVR_COLOR;

        Button(std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax);
        Button(std::string name, sf::RenderWindow* window, int x, int y);
        Button(WindowControl* winCtrl, WindowControl::State nextState, std::string name, sf::RenderWindow* window, int x, int y);

        virtual void draw();
        virtual void update(sf::Event* event);
        // virtual bool checkReadyForNextState();

        bool getIsJustPressed();

        virtual ~Button();
    private:
        void init(int txtSize, sf::Color txtColor, int xMin, int yMin, int xMax, int yMax, sf::Color btnColor,
            WindowControl::State nextState = WindowControl::State::startInit, WindowControl* winCtrl = nullptr);
        bool checkInBounds(int x, int y);

        int xMin, yMin, xMax, yMax; //possible todo move x, y to element
        sf::RectangleShape* rect;
        sf::Text* title;

        sf::Color buttonColor, hoverColor;

        bool isJustPressed, isHoveredOver;

        WindowControl::State nextState;
        WindowControl* winCtrl;

};

#endif