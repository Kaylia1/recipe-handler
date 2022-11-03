#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../include/recipe.h"
#include "../include/whole_ingredient.h"
#include "../include/file_manager.h"
#include "../include/windowControl.h"


int main() {

    FileManager* saveData = new FileManager("./save-data/ingredient_costs.txt", "./save-data/recipes.txt");
    
    saveData->loadIngredients();
    saveData->loadRecipes();

    WindowControl* winCtrl = new WindowControl();

    // Run
    while (winCtrl->isOpened()) {
        winCtrl->update();
    }

    // must close window properly to save
    saveData->writeIngredientsToFile();
    saveData->writeRecipesToFile();

    delete saveData;
    delete winCtrl;

    return 0;
}