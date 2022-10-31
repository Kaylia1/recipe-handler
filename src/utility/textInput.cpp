#include "../../include/utility/textInput.h"


TextInput::TextInput(std::string name, sf::RenderWindow* window, int y) : Element(name, window) {
    text = nullptr;
    rect = nullptr;
    init(100, y, window->getSize().x - 100, y + 25);
}

TextInput::TextInput(std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax) : Element(name, window) {
    text = nullptr;
    rect = nullptr;
    init(xMin, yMin, xMax, yMax);
}

void TextInput::init(int xMin, int yMin, int xMax, int yMax) {
    int temp;
    if(xMin > xMax) {
        temp = xMax;
        xMax = xMin;
        xMin = temp;
    }
    if(yMin > yMax) {
        temp = yMax;
        yMax = yMin;
        yMin = temp;
    }

    this->xMin = xMin;
    this->yMin = yMin;
    this->xMax = xMax;
    this->yMax = yMax;
    index = -1;

    delete text;
    text = new sf::Text();
    text->setFillColor(sf::Color::Black);
    text->setCharacterSize(18);
    text->setFont(*font);
    text->setPosition(sf::Vector2f(xMin, yMin));

    delete rect;
    rect = new sf::RectangleShape(sf::Vector2f((float) (xMax - xMin), (float) (yMax - yMin)));
    rect->setFillColor(sf::Color(240, 240, 240));
    rect->setPosition(sf::Vector2f((float) xMin, (float) yMin));
    
}

void TextInput::draw() {
    text->setString(curText);

    if(index >= 0) {
        rect->setFillColor(sf::Color(220, 220, 255));
    } else {
        rect->setFillColor(sf::Color(240, 240, 240));
    }


    window->draw(*rect);
    window->draw(*text);
}

void TextInput::update(sf::Event* event) {

    int mouseX = sf::Mouse::getPosition(*window).x;
    int mouseY = sf::Mouse::getPosition(*window).y;

    if(event->type == sf::Event::MouseButtonPressed) {
        if(mouseX >= xMin && mouseX <= xMax && mouseY >= yMin && mouseY <= yMax){ //being selected
            if(index < 0) {
                index = curText.size();
            }
        } else { //being unselected
            index = -1;
        }
        //todo: support selecting text in middle of string, would need to know font character widths
    } else if(index >= 0 && event->type == sf::Event::TextEntered && event->text.unicode < 128) { // text entered and selected
        if(index > 0 && event->text.unicode == 8) { //backspace and curText not empty
            curText.erase(index - 1, 1);
            index--;
        } else {
            curText += static_cast<char>(event->text.unicode);
            index++;
        }
        //possible todo: 127 del, arrows, enter
    }
}

TextInput::~TextInput() {

}