#ifndef TXT_IN
#define TXT_IN

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "element.h"
#include "button.hpp"

// template<class Actionable> class Button;

class TextInput : public Element {
    public:
        static const int SEARCH_BUTTON_WIDTH;
    
        TextInput(std::string name, sf::RenderWindow* window, int y);
        TextInput(std::string name, sf::RenderWindow* window, int minX, int minY, int maxX, int maxY);
        virtual void draw();
        virtual void update(sf::Event* event, int mouseX, int mouseY);

        std::string getEnteredText();
        
        void shiftDown(int yOffset);

        virtual ~TextInput();
    protected:
        void init(int minX, int minY, int maxX, int maxY);
        virtual void mouseClick(int mouseX, int mouseY);
        virtual void updateInput(Button<TextInput> *id = nullptr);

        std::string curText;
        std::string enteredText;
        std::string showText; //todo truncate to make illusion of scrolling
        int index; //points to location where next adding character. -1 when not selected
        int xMin, xMax, yMin, yMax;

        sf::Text* text;
        sf::RectangleShape* rect;
        Button<TextInput>* searchButton;
};

#endif