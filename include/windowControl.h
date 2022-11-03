#ifndef WIN_CONTROL
#define WIN_CONTROL

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <string>
#include <map>
#include <vector>
#include <iostream>

class Element;

#include "utility/button.hpp" //also includes button.h
#include "utility/element.h"
#include "utility/simpleText.h"
#include "utility/textInput.h"
#include "utility/scrollbarLayout.h"


class WindowControl {
    public:

        static const int WIDTH, HEIGHT;
        static const std::string START_BUTTON, START_TXT;

        // todo
        enum State {
            startInit,
            menuInit,

            search,
            displayRecipe,
            displayIngredient,
            newRecipe,
            newIngredient,
            editRecipe,
            editIngredient,

            main
        };

        WindowControl();
        void update();
        bool isOpened();

        // button methods
        void setMenuState(Button<WindowControl>* id);

        ~WindowControl();
    private:
        void initStart();
        void initMenu();

        void updateWindow();
        void clearElements();

        State curState, nextState;
        sf::RenderWindow* window;

        //TODO make into vector, don't really need to know id of elements
        // std::map<std::string, Element*> elements;
        std::vector<Element*> elements;
};

#endif