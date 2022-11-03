#include "../../include/utility/element.h"


sf::Font* Element::font = nullptr; //remember to call initFonts()

Element::Element(std::string name, sf::RenderWindow* window) {
    this->name = name;
    this->window = window;
    isEnabled = true;
}

void Element::update(){}

void Element::setEnabled(bool enabled) {
    isEnabled = enabled;
}

void Element::initFonts() {
    font = new sf::Font();
    if(!font->loadFromFile("Sansation-Regular.ttf")) {
        printf("ERROR failed to load font\n");
    }
}

Element::~Element(){}