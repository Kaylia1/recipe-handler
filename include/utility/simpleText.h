#ifndef SIMPLE_TXT
#define SIMPLE_TXT

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "element.h"

/**
 * Wrapper class of sf::Text to be compatible with Element
 * */
class SimpleText : public Element {
    public:
        static const sf::Color STD_TXT_CLR;
        static const int STD_TXT_SIZE;

        SimpleText(std::string name, sf::RenderWindow* window, int x, int y, sf::Color txtClr = STD_TXT_CLR, int fontSize = STD_TXT_SIZE);
        virtual void draw();
        virtual void update(sf::Event* event, int mouseX, int mouseY);
        // virtual void offset(int x, int y);
        virtual ~SimpleText();
    private:
        sf::Text* text;
        sf::Color txtClr;
        int minX;
        int minY;
        int fontSize;
};

#endif