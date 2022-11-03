#ifndef TXT_IN
#define TXT_IN

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "element.h"

class TextInput : public Element {
    public:
        TextInput(std::string name, sf::RenderWindow* window, int y);
        TextInput(std::string name, sf::RenderWindow* window, int minX, int minY, int maxX, int maxY);
        virtual void draw();
        virtual void update(sf::Event* event, int mouseX, int mouseY);
        // virtual void offset(int x, int y);
        virtual ~TextInput();
    private:
        void init(int minX, int minY, int maxX, int maxY);

        std::string curText;
        std::string showText; //todo truncate to make illusion of scrolling
        int index; //points to location where next adding character. -1 when not selected
        int xMin, xMax, yMin, yMax;

        sf::Text* text;
        sf::RectangleShape* rect;
};

#endif