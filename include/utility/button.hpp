#ifndef BUTTON_IMPLEMENTATION
#define BUTTON_IMPLEMENTATION

#include "button.h"

template<class Actionable> const int Button<Actionable>::STD_WIDTH = 50;
template<class Actionable> const int Button<Actionable>::STD_HEIGHT = 20;
template<class Actionable> const int Button<Actionable>::STD_TXT_SIZE = 24;
template<class Actionable> const sf::Color Button<Actionable>::STD_TXT_COLOR = sf::Color(0, 0, 0);
template<class Actionable> const sf::Color Button<Actionable>::STD_BTN_COLOR = sf::Color(200, 200, 255);
template<class Actionable> const sf::Color Button<Actionable>::STD_BTN_HVR_COLOR = sf::Color(180, 180, 235);

template<class Actionable> Button<Actionable>::Button(Actionable* actionable, void (Actionable::*classAction)(Button<Actionable>* id), std::string name, sf::RenderWindow* window, int x, int y) : Element(name, window){
    this->classAction = classAction;
    action = nullptr;
    title = nullptr;
    rect = nullptr;
    init(STD_TXT_SIZE, STD_TXT_COLOR, x - STD_WIDTH / 2, y - STD_HEIGHT / 2, x + STD_WIDTH / 2, y + STD_WIDTH / 2, STD_BTN_COLOR, actionable);
}

template<class Actionable> Button<Actionable>::Button(Actionable* actionable, void (Actionable::*classAction)(Button<Actionable>* id), std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax) : Element(name, window){
    this->classAction = classAction;
    action = nullptr;
    title = nullptr;
    rect = nullptr;
    init(STD_TXT_SIZE, STD_TXT_COLOR, xMin, yMin, xMax, yMax, STD_BTN_COLOR, actionable);
}

template<class Actionable> Button<Actionable>::Button(void (*action)(Button<Actionable>* id), std::string name, sf::RenderWindow* window, int x, int y) : Element(name, window){
    classAction = nullptr;
    this->action = action;
    title = nullptr;
    rect = nullptr;
    init(STD_TXT_SIZE, STD_TXT_COLOR, x - STD_WIDTH / 2, y - STD_HEIGHT / 2, x + STD_WIDTH / 2, y + STD_WIDTH / 2, STD_BTN_COLOR);
}

template<class Actionable> Button<Actionable>::Button(void (*action)(Button<Actionable>* id), std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax) : Element(name, window){
    classAction = nullptr;
    this->action = action;
    title = nullptr;
    rect = nullptr;
    init(STD_TXT_SIZE, STD_TXT_COLOR, xMin, yMin, xMax, yMax, STD_BTN_COLOR);
}

template<class Actionable> void Button<Actionable>::init(int txtSize, sf::Color txtColor, int xMin, int yMin, int xMax, int yMax, sf::Color btnColor,
    Actionable* actionable) {
        // printf("creating with %d %d\n", xMin, yMin);
    if(xMin > xMax) {
        int temp = xMin;
        xMin = xMax;
        xMax = temp;
    }
    if(yMin > yMax) {
        int temp = yMin;
        yMin = yMax;
        yMax = temp;
    }

    delete title;
    title = new sf::Text();

    title->setString(name);
    title->setFillColor(txtColor);
    title->setCharacterSize(txtSize);
    title->setFont(*font);
    // center text on button
    titleX = (xMin + xMax) / 2.0 - title->getLocalBounds().width / 2.0;
    titleY = (yMin + yMax) / 2.0 - title->getLocalBounds().height;
    title->setPosition(sf::Vector2f(titleX, titleY));
    
    buttonColor = btnColor;
    hoverColor = STD_BTN_HVR_COLOR;
    
    delete rect;
    rect = new sf::RectangleShape(sf::Vector2f((float) (xMax - xMin), (float) (yMax - yMin)));
    rect->setFillColor(buttonColor);
    rect->setPosition(sf::Vector2f((float) xMin, (float) yMin));

    this->xMin = xMin;
    this->yMin = yMin;
    this->xMax = xMax;
    this->yMax = yMax;

    isJustPressed = false;
    isHoveredOver = false;

    this->actionable = actionable;
}


template<class Actionable> void Button<Actionable>::draw() {
    if(window == nullptr) {
        printf("ERROR window is null in button draw\n");
        return;
    }

    if(!isHoveredOver) {
        rect->setFillColor(buttonColor);
    } else {
        rect->setFillColor(hoverColor);
    }

    rect->setSize(sf::Vector2f((float) (xMax - xMin), (float) (yMax - yMin)));
    rect->setPosition(sf::Vector2f((float) xMin, (float) yMin));

    window->draw(*rect);
    window->draw(*title);
}

template<class Actionable> void Button<Actionable>::update(sf::Event* event, int mouseX, int mouseY) {
    isHoveredOver = checkInBounds(mouseX, mouseY);

    if(isEnabled && event->type == sf::Event::MouseButtonPressed && isHoveredOver){
        isJustPressed = isHoveredOver; //updates every mouse click

        if (actionable != nullptr) {
            (actionable->*classAction)(this);
        } else if (action != nullptr) {
            (*action)(this);
        } else {
            printf("Warning: nullptr action passed to button\n");
        }

    }
}

template<class Actionable> void Button<Actionable>::setTitle(std::string newTitle) {
    title->setString(newTitle);
}

template<class Actionable> std::string Button<Actionable>::getTitle() {
    if(title != nullptr) {
        return title->getString().toAnsiString();
    } else {
        return "";
    }
}

template<class Actionable> bool Button<Actionable>::getIsJustPressed() {
    return isJustPressed;
}

template<class Actionable> void Button<Actionable>::changeSize(int xMin, int yMin, int xMax, int yMax) {
    int offsetX = xMin - this->xMin;
    int offsetY = yMin - this->yMin;
    this->xMin = xMin;
    this->xMax = xMax;
    this->yMin = yMin;
    this->yMax = yMax;

    titleX += offsetX;
    titleY += offsetY;
    title->setPosition(sf::Vector2f(titleX, titleY));
}

template<class Actionable> bool Button<Actionable>::checkInBounds(int x, int y) {
    return x >= xMin && x <= xMax && y >= yMin && y <= yMax;
}

template<class Actionable> Button<Actionable>::~Button(){
    delete title;
    delete rect;
}

#endif