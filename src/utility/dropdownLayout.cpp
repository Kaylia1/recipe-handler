#include "../../include/utility/dropdownLayout.h"

const int DropdownLayout::OPTION_HEIGHT = 20;

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
        options.push_back(new Button<DropdownLayout>(this, &DropdownLayout::select, preloadedOptions[i], window,
            xMin, yMin + i * OPTION_HEIGHT, xMax, yMin + (i + 1) * OPTION_HEIGHT));
    }
}

void DropdownLayout::clear() {
    options.clear();
}

void DropdownLayout::addOption(std::string opt) {
    options.push_back(new Button<DropdownLayout>(this, &DropdownLayout::select, opt, window, xMin, yMin + options.size() * OPTION_HEIGHT, xMax, yMin + (options.size() + 1) * OPTION_HEIGHT));
    // options.push_back(new Button<DropdownLayout>(this, &DropdownLayout::select, opt, window, 0, 0, 500, 500));
}

void DropdownLayout::select(Button<DropdownLayout>* id) {
    isSelected = true;
    // printf("selected\n");
    selectedOption = id->getTitle();
}

bool DropdownLayout::getSelected() {
    return isSelected;
}

std::string DropdownLayout::getCurOption() { //true max once per update, updates each update
// printf("I am %d\n", isSelected);
    return (isSelected)? selectedOption : "";
}

//todo visual queue to see what is selected, possibly add drop down option
void DropdownLayout::draw() {
    // printf("buttons to draw is %d", options.size());
    for(unsigned long i = 0; i < options.size(); i++) {
        options[i]->draw();
    }
}

void DropdownLayout::update(sf::Event* event, int mouseX, int mouseY) {
    // printf("unselected\n");
    isSelected = false;
    for(unsigned long i = 0; i < options.size(); i++) {
        options[i]->update(event, mouseX, mouseY);
    }
}

DropdownLayout::~DropdownLayout(){
    for(unsigned long i = 0; i < options.size(); i++) {
        delete options[i];
    }
}
