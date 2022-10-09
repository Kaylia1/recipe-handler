#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../include/recipe.h"
#include "../include/ingredient.h"
#include "../include/file_manager.h"

int main() {

    sf::Window window(sf::VideoMode(800, 600), "Recipe management");

    // Ingredient* test = new Ingredient();
    FileManager* saveData = new FileManager("./save-data/ingredient_costs.txt", "./save-data/recipes.txt");
    saveData->loadIngredients();

    // Run
    while (window.isOpen())
    {
        // Check all window events from iter
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
    }

    delete saveData;

    return 0;
}