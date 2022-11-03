#ifndef BUTTON
#define BUTTON

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

#include "element.h"

template<class Actionable> class Button : public Element {
    public:

        static const int STD_WIDTH;
        static const int STD_HEIGHT;
        static const int STD_TXT_SIZE;
        static const sf::Color STD_TXT_COLOR;
        static const sf::Color STD_BTN_COLOR;
        static const sf::Color STD_BTN_HVR_COLOR;

        // has action which is a member function
        Button(Actionable* actionable, void (Actionable::*classAction)(Button<Actionable>* id), std::string name, sf::RenderWindow* window, int x, int y);
        Button(Actionable* actionable, void (Actionable::*classAction)(Button<Actionable>* id), std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax);
        // has action which is a global function
        Button(void (*action)(Button<Actionable>* id), std::string name, sf::RenderWindow* window, int x, int y);
        Button(void (*action)(Button<Actionable>* id), std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax);

        virtual void draw();
        virtual void update(sf::Event* event, int mouseX, int mouseY);

        bool getIsJustPressed();
        std::string getTitle();

        virtual ~Button();
    protected:
        void init(int txtSize, sf::Color txtColor, int xMin, int yMin, int xMax, int yMax, sf::Color btnColor,
            Actionable* actionable = nullptr);
        bool checkInBounds(int x, int y);

        // calls action and passes in pointer to itself to identify which element initiated the action
        void (Actionable::*classAction) (Button<Actionable>* id);
        void (*action) (Button<Actionable>* id);


        int xMin, yMin, xMax, yMax;
        sf::RectangleShape* rect;
        sf::Text* title;

        sf::Color buttonColor, hoverColor;

        bool isJustPressed; //whether last click was button click
        bool isHoveredOver;

        Actionable* actionable;

};

#endif