#include "../../include/utility/windowControl.h"

const int WindowControl::WIDTH = 800;
const int WindowControl::HEIGHT = 600;

const std::string WindowControl::START_BUTTON = "start";

WindowControl::WindowControl() {
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Recipe management");
    // printf("CHECKING %p\n", window);
    curState = startInit;
}

/**
 * returns whether to stop updating
 * */
void WindowControl::update(){

    switch(curState) {
        case startInit:
            initStart();
            curState = start;
            break;
        case start:
            updateStart();
            break;
    }
}

bool WindowControl::isOpened(){
    return window != nullptr && window->isOpen();
}

void WindowControl::initStart(){
    buttons[START_BUTTON] = new Button(START_BUTTON, window, WIDTH / 2, HEIGHT / 2);
}

/**
 * Updates window for given state and event.
 * */
void WindowControl::updateStart(){

    window->clear();
    buttons[START_BUTTON]->draw();
    window->display();

    sf::Event event;
    while (window->pollEvent(event))
    {

        // Close window
        if (event.type == sf::Event::Closed){
            window->close();
        }
    }
    
}

WindowControl::~WindowControl(){
    delete window;
    for(std::map<std::string, Button*>::iterator iter = buttons.begin(); iter != buttons.end(); iter++) {
        delete iter->second;
    }
}