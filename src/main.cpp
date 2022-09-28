#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../include/recipe.h"
#include "../include/ingredient.h"

int main() {

    sf::Window window(sf::VideoMode(800, 600), "My window");
    while(window.isOpen()) {
        window.display();
    }
    printf("hello world");

    return 0;
}