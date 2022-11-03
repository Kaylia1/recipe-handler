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
// #include "utility/button.hpp"
// #include "windowControl.h"

class DivisibleIngredient;
class WholeIngredient;
class Recipe;
// class WindowControl;

class FileManager {
    public:
        FileManager(std::string ingredientPath, std::string recipePath);
        void loadIngredients(); //TODO bool return val
        void loadRecipes();
        void writeIngredientsToFile();
        void writeRecipesToFile();

    //todo translate to gen layout
        void displayIngredients(sf::RenderWindow *window); //TODO
        void displayRecipes(sf::RenderWindow *window);

        //TODO
        void addIngredient();
        void addRecipe();

        // void expandRecipe(Button<FileManager> *id);

        ~FileManager();
    private:
        std::string ingredientPath, recipePath;

        // currently using name as ID to prevent duplicate names, may consider numbers
        std::map<std::string, WholeIngredient*> allIngredients;
        std::map<std::string, Recipe*> allRecipes; //todo make pair of recipe and recipeDisplay
};

#endif