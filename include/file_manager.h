#ifndef FILE_MANAGER
#define FILE_MANAGER

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

#include "divisible_ingredient.h"
#include "whole_ingredient.h"
#include "recipe.h"

class DivisibleIngredient;
class WholeIngredient;
class Recipe;

class FileManager {
    public:
        FileManager(std::string ingredientPath, std::string recipePath);
        void loadIngredients(); //TODO bool return val
        void loadRecipes();
        void writeIngredientsToFile();
        void writeRecipesToFile();

        //TODO
        void addIngredient();
        void addRecipe();

        ~FileManager();
    private:
        std::string ingredientPath, recipePath;

        // currently using name as ID to prevent duplicate names, may consider numbers
        std::map<std::string, WholeIngredient*> allIngredients;
        std::map<std::string, Recipe*> allRecipes;
};

#endif