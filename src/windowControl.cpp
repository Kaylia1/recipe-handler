#include "../include/windowControl.h"

const int WindowControl::WIDTH = 800;
const int WindowControl::HEIGHT = 600;

const std::string WindowControl::START_BUTTON = "start";
const std::string WindowControl::START_TXT = "Welcome to Recipe Manager!";

WindowControl::WindowControl() {
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Recipe management");
    curState = startInit;
    nextState = main;
    Element::initFonts();
}

/**
 * returns whether to stop updating
 * */
void WindowControl::update(){

    switch(curState) {
        case startInit:
            initStart();
            break;
        case menuInit:
            initMenu();
            break;
        case main:
            updateWindow();
            break;
    }
    curState = nextState;
}

bool WindowControl::isOpened(){
    return window != nullptr && window->isOpen();
}

void WindowControl::initStart(){
    clearElements();
    elements.push_back(new SimpleText(START_TXT, window, WIDTH / 2, HEIGHT / 2 - 50));
    elements.push_back(new Button<WindowControl>(this, &WindowControl::setMenuState, START_BUTTON, window, WIDTH / 2, HEIGHT / 2 + 100));
    nextState = main;
}

void WindowControl::initMenu() {
    clearElements();
    elements.push_back(new TextInput("searchbar", window, 100));

    ScrollbarLayout* scrollbar = new ScrollbarLayout("menu", window, WIDTH, HEIGHT, 100, 200, window->getSize().x - 100*2, 300, 1000);
    elements.push_back(scrollbar);
    
    scrollbar->addInnerElement(new Button<WindowControl>(this, &WindowControl::setMenuState, START_BUTTON, window, 0, scrollbar->translateInnerElementY(500)));
    
    nextState = main;
}


/**
 * Updates window for given state and event.
 * */
void WindowControl::updateWindow(){

    window->clear(sf::Color::White);

    for(unsigned long i = 0; i < elements.size(); i++) {
        elements[i]->draw();
    }

    window->display();

    sf::Event event;
    while (window->pollEvent(event))
    {
        int mouseX = sf::Mouse::getPosition(*window).x;
        int mouseY = sf::Mouse::getPosition(*window).y;

        for(unsigned long i = 0; i < elements.size(); i++) {
            elements[i]->update(&event, mouseX, mouseY);
        }

        // Close window
        if (event.type == sf::Event::Closed){
            window->close();
        }
    }
    for(unsigned long i = 0; i < elements.size(); i++) {
        elements[i]->update();
    }
    
}

void WindowControl::setMenuState(Button<WindowControl>* id) {
    nextState = menuInit;
}

void WindowControl::clearElements() {
    for(unsigned long i = 0; i < elements.size(); i++){
        delete elements[i];
    }
    elements.clear();
}

WindowControl::~WindowControl(){
    delete window;
    clearElements();
}