#ifndef RECIPE_DISPLAY
#define RECIPE_DISPLAY

#include <sstream>

#include "utility/button.hpp"
#include "recipe.h"

/**
 * Functionally like a button, except clicking it expands title into info.
*/
class RecipeDisplay : public Button<RecipeDisplay> {
    public:
        static const int TITLE_HEIGHT = 20;

        RecipeDisplay(sf::RenderWindow *window, Recipe* recipe, int xMin, int yMin, int width);

        // virtual void update(sf::Event *event, int mouseX, int mouseY);

        void activate(Button<RecipeDisplay>* id);

        virtual ~RecipeDisplay();
    private:

        std::string listIngredients();
        std::string listSteps();
        std::string listNotes();

        Recipe* recipe;

        bool isExpanded;

};

#endif