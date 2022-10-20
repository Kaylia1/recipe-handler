#include "../../include/utility/element.h"


sf::Font* Element::font = nullptr; //remember to call initFonts()

Element::Element(std::string name, sf::RenderWindow* window) {
    this->name = name;
    this->window = window;
}

void Element::initFonts() {
    font = new sf::Font();
    if(!font->loadFromFile("Sansation-Regular.ttf")) {
        printf("ERROR failed to load font\n");
    }
}

// bool Element::checkReadyForNextState() {
//     return false;
// }

Element::~Element(){}