#include "../../include/utility/button.h"

const int Button::STD_WIDTH = 20;
const int Button::STD_HEIGHT = 10;

Button::Button(std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax) {
    init(name, window, xMin, yMin, xMax, yMax);
}

Button::Button(std::string name, sf::RenderWindow* window, int x, int y) {
    init(name, window, x - STD_WIDTH / 2, y - STD_HEIGHT / 2, x + STD_WIDTH / 2, y + STD_WIDTH / 2);
}

void Button::init(std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax) {
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
    title->setFillColor(sf::Color::Red);
    // center text on button
    title->setPosition(sf::Vector2f((float)((xMin + xMax) / 2.0 - title->getLocalBounds().width / 2.0),
                                    (float)((yMin + yMax) / 2.0 - title->getLocalBounds().height / 2.0)));

    this->window = window;
    rect = new sf::RectangleShape(sf::Vector2f((float) (xMax - xMin), (float) (yMax - yMin)));
    rect->setFillColor(sf::Color::Blue);
    rect->setPosition(sf::Vector2f((float) xMin, (float) yMin));

    this->xMin = xMin;
    this->yMin = yMin;
    this->xMax = xMax;
    this->yMax = yMax;
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