#include "../../include/utility/simpleText.h"

const sf::Color SimpleText::STD_TXT_CLR = sf::Color(0, 0, 0);
const int SimpleText::STD_TXT_SIZE = 24;

SimpleText::SimpleText(std::string name, sf::RenderWindow* window, int x, int y, sf::Color txtClr, int fontSize) : Element(name, window) {
    text = new sf::Text();
    text->setString(name);
    this->txtClr = txtClr;
    text->setFillColor(txtClr);
    this->fontSize = fontSize;
    text->setCharacterSize(fontSize);
    text->setFont(*font);
    // center text on button
    minX = x - text->getLocalBounds().width / 2;
    minY = y - text->getLocalBounds().height;
    text->setPosition(sf::Vector2f(minX, minY));
}

void SimpleText::draw(){
    window->draw(*text);
}

void SimpleText::update(sf::Event* event){}

SimpleText::~SimpleText() {
    delete text;
}