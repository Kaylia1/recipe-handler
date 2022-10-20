#ifndef TXT_IN
#define TXT_IN

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "element.h"

class TextInput : public Element {
    public:
        TextInput(); //todo
        virtual void draw();
        virtual void update(sf::Event* event);
        ~TextInput();
    private:
        std::string curText;
        std::string showText; //todo truncate to make illusion of scrolling
        int index; //points to location where next adding character. -1 when not selected
        int minX, minY, maxX, maxY; //todo

        sf::RenderWindow* window;
};

#endif