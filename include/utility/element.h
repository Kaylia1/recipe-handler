#ifndef ELEMENT
#define ELEMENT

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
// #include "windowControl.h"

class Element {
    public:
        Element(std::string name, sf::RenderWindow* window);

        virtual void update(sf::Event* event) = 0;
        virtual void draw() = 0;

        // for action events to override
        // virtual bool checkReadyForNextState();

        static void initFonts();

        virtual ~Element();
    protected:
        std::string name; //identifier

        sf::RenderWindow* window;
        static sf::Font* font;
};

#endif