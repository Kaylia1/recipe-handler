#include "../../include/utility/button.h"

const int Button::STD_WIDTH = 50;
const int Button::STD_HEIGHT = 20;
const int Button::STD_TXT_SIZE = 24;
const sf::Color Button::STD_TXT_COLOR = sf::Color(0, 0, 0);
const sf::Color Button::STD_BTN_COLOR = sf::Color(200, 200, 255);
const sf::Color Button::STD_BTN_HVR_COLOR = sf::Color(180, 180, 235);

Button::Button(std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax) : Element(name, window){
    action = nullptr;
    title = nullptr;
    rect = nullptr;
    init(STD_TXT_SIZE, STD_TXT_COLOR, xMin, yMin, xMax, yMax, STD_BTN_COLOR);
}

Button::Button(std::string name, sf::RenderWindow* window, int x, int y) : Element(name, window){
    action = nullptr;
    title = nullptr;
    rect = nullptr;
    init(STD_TXT_SIZE, STD_TXT_COLOR, x - STD_WIDTH / 2, y - STD_HEIGHT / 2, x + STD_WIDTH / 2, y + STD_WIDTH / 2, STD_BTN_COLOR);
}

Button::Button(WindowControl* winCtrl, void (WindowControl::*action)(), std::string name, sf::RenderWindow* window, int x, int y) : Element(name, window){
    this->action = action;
    title = nullptr;
    rect = nullptr;
    init(STD_TXT_SIZE, STD_TXT_COLOR, x - STD_WIDTH / 2, y - STD_HEIGHT / 2, x + STD_WIDTH / 2, y + STD_WIDTH / 2, STD_BTN_COLOR, winCtrl);
}

void Button::init(int txtSize, sf::Color txtColor, int xMin, int yMin, int xMax, int yMax, sf::Color btnColor,
    WindowControl* winCtrl) {

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
    title->setPosition(sf::Vector2f((float)((xMin + xMax) / 2.0 - title->getLocalBounds().width / 2.0),
                                    (float)((yMin + yMax) / 2.0 - title->getLocalBounds().height)));
    
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

    this->winCtrl = winCtrl;
}


void Button::draw() {
    if(window == nullptr) {
        printf("ERROR window is null in button draw\n");
        return;
    }

    if(!isHoveredOver) {
        rect->setFillColor(buttonColor);
    } else {
        rect->setFillColor(hoverColor);
    }

    window->draw(*rect);
    window->draw(*title);
}

void Button::update(sf::Event* event) {
    isHoveredOver = checkInBounds(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

    if(event->type == sf::Event::MouseButtonPressed){
        isJustPressed = isHoveredOver;

        if (winCtrl != nullptr) {
            (winCtrl->*action)();
        }

    }
}

std::string Button::getTitle() {
    if(title != nullptr) {
        return title->getString().toAnsiString();
    } else {
        return "";
    }
}

bool Button::getIsJustPressed() {
    return isJustPressed;
}

bool Button::checkInBounds(int x, int y) {
    return x >= xMin && x <= xMax && y >= yMin && y <= yMax;
}

Button::~Button(){
    delete title;
    delete rect;
}