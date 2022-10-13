#ifndef FILE_MANAGER
#define FILE_MANAGER

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

#include "ingredient.h"
#include "recipe.h"

class Ingredient;
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

    //void saveIngredients();
    //void saveRecipes();
    ~FileManager();
  private:
    std::string ingredientPath, recipePath;
    std::map<std::string, Ingredient*> allIngredients;
    std::map<std::string, Recipe*> allRecipes;
};

#endif