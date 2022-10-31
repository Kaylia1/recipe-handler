#include "../../include/utility/dropdownLayout.h"

const int DropdownLayout::OPTION_HEIGHT = 70;

DropdownLayout::DropdownLayout(std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax) : Element(name, window){
    this->xMin = xMin;
    this->yMin = yMin;
    this->xMax = xMax;
    selectedOption = "";
}

DropdownLayout::DropdownLayout(std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, std::string preloadedOptions[], int numLoaded) : Element(name, window){
    this->xMin = xMin;
    this->yMin = yMin;
    this->xMax = xMax;
    selectedOption = "";
    for(int i = 0; i < numLoaded; i++) {
        options.push_back(Button<DropdownLayout>(this, &DropdownLayout::select, preloadedOptions[i], window, xMin, yMin + i * OPTION_HEIGHT, xMax, yMin + i * (OPTION_HEIGHT + 1)));
    }
}

void DropdownLayout::addOption(std::string opt) {
    options.push_back(Button<DropdownLayout>(this, &DropdownLayout::select, opt, window, xMin, yMin + options.size() * OPTION_HEIGHT, xMax, yMin + options.size() * (OPTION_HEIGHT + 1)));
}

void DropdownLayout::select(Button<DropdownLayout>* id) {
    selectedOption = id->getTitle();
}

std::string DropdownLayout::getCurOption() {
    return selectedOption;
}

//todo visual queue to see what is selected, possibly add drop down option
void DropdownLayout::draw() {
    for(unsigned long i = 0; i < options.size(); i++) {
        options[i].draw();
    }
}

void DropdownLayout::update(sf::Event* event) {
    for(unsigned long i = 0; i < options.size(); i++) {
        options[i].update(event);
    }
}

DropdownLayout::~DropdownLayout(){

}
