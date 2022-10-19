#ifndef WIN_CONTROL
#define WIN_CONTROL

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <string>
#include <map>

#include "button.h"


class WindowControl {
    public:

        static const int WIDTH, HEIGHT;
        static const std::string START_BUTTON;

        // todo
        enum State {
            startInit, start,
            menu,
            search,
            displayRecipe,
            displayIngredient,
            newRecipe,
            newIngredient,
            editRecipe,
            editIngredient
        };

        WindowControl();
        void update();
        bool isOpened();
        ~WindowControl();
    private:
        void initStart();
        void updateStart();
        void updateMenu();

        State curState;
        sf::RenderWindow* window;

        std::map<std::string, Button*> buttons;
};

#endif