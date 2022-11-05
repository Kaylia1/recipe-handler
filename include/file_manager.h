#ifndef FILE_MANAGER
#define FILE_MANAGER

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

#include "divisible_ingredient.h"
#include "whole_ingredient.h"
#include "recipe.h"
#include "recipeDisplay.h"
#include "utility/element.h"


// #include "utility/button.hpp"
// #include "windowControl.h"

class DivisibleIngredient;
class WholeIngredient;
class Recipe;
// class WindowControl;
// class RecipeControl;

class FileManager : public Element {
    public:
        //singleton class, can only create one instance
        static FileManager* newFileManager(sf::RenderWindow* window, std::string ingredientPath, std::string recipePath);
        static FileManager* getFileManager();

        void loadIngredients(); //TODO bool return val
        void loadRecipes();
        void writeIngredientsToFile();
        void writeRecipesToFile();

    //todo translate to gen layout
        void displayIngredientsInit(); //TODO
        void displayRecipesInit(int centerX, int startY); //assumes want centered and top-down flow

        void draw();
        void update(sf::Event* event, int mouseX, int mouseY);

        //TODO
        void addIngredient();
        void addRecipe();

        // void expandRecipe(Button<FileManager> *id);

        ~FileManager();
    private:
        static FileManager* fileManager;
        FileManager(sf::RenderWindow *window, std::string ingredientPath, std::string recipePath);

        std::string ingredientPath, recipePath;

        // currently using name as ID to prevent duplicate names, may consider numbers
        std::map<std::string, WholeIngredient*> allIngredients;
        std::map<std::string, std::pair<Recipe*, RecipeDisplay*>> allRecipes; //todo make pair of recipe and recipeDisplay
};

#endif