#include "../../include/utility/textInput.h"

const int TextInput::SEARCH_BUTTON_WIDTH = 80;

TextInput::TextInput(std::string name, sf::RenderWindow* window, int y) : Element(name, window) {
    text = nullptr;
    rect = nullptr;
    searchButton = nullptr;
    init(100, y, window->getSize().x - 100, y + 25);
}

TextInput::TextInput(std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax) : Element(name, window) {
    text = nullptr;
    rect = nullptr;
    searchButton = nullptr;
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
    this->xMax = xMax - SEARCH_BUTTON_WIDTH;
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

    delete searchButton;
    searchButton = new Button<TextInput>(this, &TextInput::updateInput, "enter", window, this->xMax, yMin, xMax, yMax);
    searchButton->setColor(sf::Color(240, 240, 255));
    
}

void TextInput::draw() {
    text->setString(curText);

    if(index >= 0) {
        rect->setFillColor(sf::Color(230, 230, 255));
    } else {
        rect->setFillColor(sf::Color(240, 240, 240));
    }


    window->draw(*rect);
    window->draw(*text);
    searchButton->draw();
}

void TextInput::update(sf::Event* event, int mouseX, int mouseY) {

    //must be enabled to select, but don't need to keep mouse in window to type
    //can unselect when not enabled
    if(event->type == sf::Event::MouseButtonPressed) {
        mouseClick(mouseX, mouseY);
        //todo: support selecting text in middle of string, would need to know font character widths
    } else if(index >= 0 && event->type == sf::Event::TextEntered && event->text.unicode < 128) { // text entered and selected
        if(index > 0 && event->text.unicode == 8) { //backspace and curText not empty
            curText.erase(index - 1, 1);
            index--;
        } else if(event->text.unicode == 13){ //enter
            updateInput();
        } else if(event->text.unicode >= 32){ //must be text character
            curText += static_cast<char>(event->text.unicode);
            index++;
        }
        //possible todo: 127 del, arrows, enter
    }

    searchButton->update(event, mouseX, mouseY);
}

void TextInput::updateInput(Button<TextInput> *id) {
    // printf("updated input\n");
    enteredText = curText;
}

void TextInput::mouseClick(int mouseX, int mouseY) {
    //if in range of search field
    bool xInRange = mouseX >= xMin && mouseX <= xMax;
    bool yInRange = mouseY >= yMin && mouseY <= yMax;

    if(xInRange && yInRange){ //being selected
        if(isEnabled && index < 0) { //select end of string
            index = curText.size();
        }
    } else if(!(mouseX >= xMin && mouseX <= xMax + SEARCH_BUTTON_WIDTH && yInRange)){ //being unselected, search button excluded
        index = -1;
    }
}

void TextInput::shiftDown(int yOffset) {
    yMin += yOffset;
    yMax += yOffset;
    text->setPosition(sf::Vector2f((float) xMin, (float) yMin));
    rect->setPosition(sf::Vector2f((float) xMin, (float) yMin));
    searchButton->changeSize(xMax, yMin, xMax + SEARCH_BUTTON_WIDTH, yMax);

}

std::string TextInput::getEnteredText(){
    return enteredText;
}

TextInput::~TextInput() {
    delete text;
    delete rect;
    delete searchButton;
}