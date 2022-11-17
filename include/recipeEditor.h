#ifndef RECIPE_EDITOR
#define RECIPE_EDITOR

// #include <>
#include <memory> //todo learn how to use unique_ptr
#include <vector>
#include "utility/element.h"
#include "utility/textInput.h"
#include "utility/button.hpp"
// #include "utility/button.h"
#include "recipe.h"
#include "utility/scrollbarLayout.h"

/**
 * No x, y coords, soft of functions as a pop-up that fills screen
*/
class RecipeEditor : public Element {
    public:
        static const int LINE_HEIGHT;
        static const int SPACING_HEIGHT;
        static const int MIN_X_INIT, MAX_X_INIT;
        static const int MIN_X_INPUT, MAX_X_INPUT;

        RecipeEditor(sf::RenderWindow *window, int windowWidth, int windowHeight);
        void update(sf::Event *event, int mouseX, int mouseY);
        void update();
        void draw();



        ~RecipeEditor();
    private:
        //TODO needs scrollbar... either one large or one for each field

        void newIngredient(Button<RecipeEditor> *id);
        void newInstruction(Button<RecipeEditor> *id);
        void newNote(Button<RecipeEditor> *id);

        std::unique_ptr<Recipe> saveRecipe();

        TextInput enterName;

        std::shared_ptr<Button<RecipeEditor>> addIngredient;
        std::shared_ptr<Button<RecipeEditor>> addInstruction;
        std::shared_ptr<Button<RecipeEditor>> addNote;

        ScrollbarLayout recipeScrollbar;
        
        std::vector<std::shared_ptr<TextInput>> enterIngredients;
        std::vector<std::shared_ptr<TextInput>> enterInstructions;
        std::vector<std::shared_ptr<TextInput>> enterNotes;

        int ingredientY;
        int instructionY;
        int noteY; //max


};

#endif