#include "../../include/utility/button.h"

const int Button::STD_WIDTH = 50;
const int Button::STD_HEIGHT = 20;
const int Button::STD_TXT_SIZE = 24;
const sf::Color Button::STD_TXT_COLOR = sf::Color(0, 0, 0);
const sf::Color Button::STD_BTN_COLOR = sf::Color(200, 200, 255);
sf::Font* Button::font = nullptr; //remember to call initFonts()

Button::Button(std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax) {
    init(name, STD_TXT_SIZE, STD_TXT_COLOR, window, xMin, yMin, xMax, yMax, STD_BTN_COLOR);
}

Button::Button(std::string name, sf::RenderWindow* window, int x, int y) {
    init(name, STD_TXT_SIZE, STD_TXT_COLOR, window, x - STD_WIDTH / 2, y - STD_HEIGHT / 2, x + STD_WIDTH / 2, y + STD_WIDTH / 2, STD_BTN_COLOR);
}

void Button::init(std::string name, int txtSize, sf::Color txtColor, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax, sf::Color btnColor) {
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

    this->name = name;
    title = new sf::Text();
    title->setString(name);
    title->setFillColor(txtColor);
    title->setCharacterSize(txtSize);
    title->setFont(*font);
    // center text on button
    title->setPosition(sf::Vector2f((float)((xMin + xMax) / 2.0 - title->getLocalBounds().width / 2.0),
                                    (float)((yMin + yMax) / 2.0 - title->getLocalBounds().height)));
    

    this->window = window;
    rect = new sf::RectangleShape(sf::Vector2f((float) (xMax - xMin), (float) (yMax - yMin)));
    rect->setFillColor(btnColor);
    rect->setPosition(sf::Vector2f((float) xMin, (float) yMin));

    this->xMin = xMin;
    this->yMin = yMin;
    this->xMax = xMax;
    this->yMax = yMax;
}

void Button::initFonts() {
    font = new sf::Font();
    if(!font->loadFromFile("Sansation-Regular.ttf")) {
        printf("ERROR failed to load font\n");
    }
}

void Button::draw() {
    if(window == nullptr) {
        printf("ERROR window is null in button draw\n");
        return;
    }
    window->draw(*rect);
    window->draw(*title);
}

bool Button::checkInBounds(int x, int y) {
    return x >= xMin && x <= xMax && y >= yMin && y <= yMax;
}

Button::~Button(){
    delete rect;
}