#include "../../include/utility/textInput.h"

TextInput::TextInput() {
    index = -1;
}

void TextInput::draw() {

}

void TextInput::update(sf::Event* event) {

    int mouseX = sf::Mouse::getPosition(*window).x;
    int mouseY = sf::Mouse::getPosition(*window).y;

    if(event->type == sf::Event::MouseButtonPressed) {
        if(mouseX >= minX && mouseX <= maxX && mouseY >= minY && mouseY <= maxY){ //being selected
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