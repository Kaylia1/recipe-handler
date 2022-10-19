#ifndef BUTTON
#define BUTTON

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class Button {
    public:

        static const int STD_WIDTH;
        static const int STD_HEIGHT;


        Button(std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax);
        Button(std::string name, sf::RenderWindow* window, int x, int y);


        bool checkInBounds(int x, int y);
        void draw();

        ~Button();
    private:
        void init(std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax);

        std::string name;
        int xMin, yMin, xMax, yMax;
        sf::RenderWindow* window;
        sf::RectangleShape* rect;
        sf::Text* title;
};

#endif