#ifndef BUTTON
#define BUTTON

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

#include "element.h"
// #include "windowControl.h"

template<class Actionable> class Button : public Element {
    public:

        static const int STD_WIDTH;
        static const int STD_HEIGHT;
        static const int STD_TXT_SIZE;
        static const sf::Color STD_TXT_COLOR;
        static const sf::Color STD_BTN_COLOR;
        static const sf::Color STD_BTN_HVR_COLOR;

        // typedef void (OnAction) ();

        Button(std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax);
        Button(std::string name, sf::RenderWindow* window, int x, int y);

        // has action which is a member function
        Button(Actionable* actionable, void (Actionable::*classAction)(), std::string name, sf::RenderWindow* window, int x, int y);
        // has action which is a global function
        Button(void (*action)(), std::string name, sf::RenderWindow* window, int x, int y);

        virtual void draw();
        virtual void update(sf::Event* event);
        // virtual bool checkReadyForNextState();

        bool getIsJustPressed();
        std::string getTitle();

        virtual ~Button();
    private:
        void init(int txtSize, sf::Color txtColor, int xMin, int yMin, int xMax, int yMax, sf::Color btnColor,
            Actionable* actionable = nullptr);
        bool checkInBounds(int x, int y);

        void (Actionable::*classAction) ();
        void (*action) ();

        int xMin, yMin, xMax, yMax; //possible todo move x, y to element
        sf::RectangleShape* rect;
        sf::Text* title;

        sf::Color buttonColor, hoverColor;

        bool isJustPressed, isHoveredOver;

        Actionable* actionable;
        // WindowControl* winCtrl;

};

#endif