#ifndef FILE_MANAGER
#define FILE_MANAGER

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <string>
#include <map>
#include <vector>
// #include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

#include "divisibleIngredient.h"
#include "wholeIngredient.h"
#include "recipe.h"
#include "recipeDisplay.h"
#include "utility/element.h"
#include "stringSimilarity.h"


// #include "utility/button.hpp"
// #include "windowControl.h"

class DivisibleIngredient;
class WholeIngredient;
class Recipe;
// class WindowControl;
// class RecipeControl;

//todo split this class, have subclass just for file I/O
class FileManager : public Element {
    public:
        struct RecipeHolder {
            Recipe* recipe;
            int index;
            int similarityScore;
            bool operator < (const RecipeHolder& a) const {
                return similarityScore < a.similarityScore;
            }
        };

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

        int checkContainsRecipeName(std::string recipeName);

        //todo next commit
        // recipeTextInput calls scrollbar to move down
        // incorporate auto-fill with string similarity, now "co" is considered more similar to "test" than "cookies"
        // button colors so it's less ugly

        //todo return ptr to vector so can return null? if none similar enough found, should also be able to rank similarity
        RecipeHolder getMostSimilarName(std::string name);

        ~FileManager();
    private:
        // class Compare {
        //     public:
        //         bool operator() (std::pair<Recipe*, int> a, std::pair<Recipe*, int> b) {
        //             return levenshteinDistance(a.first->getName(), getFileManager()->referenceName.first->getName()) < levenshteinDistance(a.first->getName(), getFileManager()->referenceName.first->getName());
        //         }
        // };

        static FileManager* fileManager;
        FileManager(sf::RenderWindow *window, std::string ingredientPath, std::string recipePath);

        // std::pair<Recipe*, int> referenceName;
        std::string ingredientPath, recipePath;

        // currently using name as ID to prevent duplicate names, may consider numbers
        std::map<std::string, WholeIngredient*> allIngredients;
        // std::map<std::string, std::pair<Recipe*, RecipeDisplay*>> allRecipes; //todo make pair of recipe and recipeDisplay
        std::vector<std::pair<Recipe*, RecipeDisplay*>> allRecipes;
};

#endif