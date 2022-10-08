#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../include/recipe.h"
#include "../include/ingredient.h"

int main() {

    sf::Window window(sf::VideoMode(800, 600), "Recipe management");

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

    return 0;
}