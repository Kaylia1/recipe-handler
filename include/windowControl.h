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
#include "recipeTextInput.h"
#include "fileManager.h"
#include "recipeEditor.h"


class WindowControl {
    public:

        static const int WIDTH, HEIGHT;
        static const std::string START_BUTTON, START_TXT, ADD_RECIPE;

        // todo
        enum State {
            startInit,
            menuInit,
            editRecipeInit,
            
            editRecipe,
            editIngredient,

            main
        };

        WindowControl();
        void update();
        bool isOpened();

        sf::RenderWindow* getWindow();

        // button methods
        void setMenuState(Button<WindowControl>* id);
        void setEditRecipeState(Button<WindowControl>* id);

        ~WindowControl();
    private:
        void initStart();
        void initMenu();
        void initEditRecipe();

        void updateWindow();
        void clearElements();

        State curState, nextState;
        sf::RenderWindow* window;

        std::vector<Element*> elements;
};

#endif