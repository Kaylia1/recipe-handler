#ifndef BUTTON
#define BUTTON

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class Button {
    public:

        static const int STD_WIDTH;
        static const int STD_HEIGHT;
        static const int STD_TXT_SIZE;
        static const sf::Color STD_TXT_COLOR;
        static const sf::Color STD_BTN_COLOR;

        Button(std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax);
        Button(std::string name, sf::RenderWindow* window, int x, int y);

        static void initFonts();

        bool checkInBounds(int x, int y);
        void draw();

        ~Button();
    private:
        void init(std::string name, int txtSize, sf::Color txtColor, sf::RenderWindow* window, int xMin, int yMin, int xMax, int yMax, sf::Color btnColor);

        std::string name;
        int xMin, yMin, xMax, yMax;
        sf::RenderWindow* window;
        sf::RectangleShape* rect;
        sf::Text* title;

        static sf::Font* font;
};

#endif