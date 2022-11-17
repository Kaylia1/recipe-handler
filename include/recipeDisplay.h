#ifndef RECIPE_DISPLAY
#define RECIPE_DISPLAY

#include <sstream>

#include "utility/button.hpp"
#include "utility/element.h"
#include "recipe.h"

/**
 * Functionally like a button, except clicking it expands title into info.
*/
class RecipeDisplay : public Element {
    public:
        static const int TITLE_HEIGHT = 27;
        static const int LINE_HEIGHT = 13;

        enum StateChange {
            none,
            expanded,
            minimized
        };

        RecipeDisplay(sf::RenderWindow *window, Recipe* recipe, int xMin, int yMin, int width);

        // virtual void update(sf::Event *event, int mouseX, int mouseY);

        void activate(Button<RecipeDisplay>* id);
        void shiftYVal(int offset);
        int getMinY();
        double getExtraHeight();
        StateChange getChanged();

        void draw();
        void update(sf::Event *event, int mouseX, int mouseY);

        virtual ~RecipeDisplay();
    private:

        Button<RecipeDisplay> *display;

        std::string listIngredients();
        std::string listSteps();
        std::string listNotes();

        Recipe* recipe;
        sf::Text* mainText;

        int xMin, xMax, yMin, yMax;
        bool isExpanded;
        StateChange justChanged;

        std::string expandedText;
        int expandedSize;

};

#endif