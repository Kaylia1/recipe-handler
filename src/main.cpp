#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../include/recipe.h"
#include "../include/wholeIngredient.h"
#include "../include/fileManager.h"
#include "../include/windowControl.h"


int main() {
    
    WindowControl* winCtrl = new WindowControl();

    FileManager* saveData = FileManager::newFileManager(winCtrl->getWindow(), "./save-data/ingredient_costs.txt", "./save-data/recipes.txt");
    
    saveData->loadIngredients();
    saveData->loadRecipes();


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