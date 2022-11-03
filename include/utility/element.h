#ifndef ELEMENT
#define ELEMENT

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Element {
    public:
        Element(std::string name, sf::RenderWindow* window);

        virtual void update(sf::Event* event, int mouseX, int mouseY) = 0; //update per event
        virtual void update(); //one update
        virtual void draw() = 0;
        virtual void setEnabled(bool enabled);

        //for layout management
        //todo figure out how to offset and enable things
        // virtual void offset(int x, int y) = 0; //TODO implement this everywhere

        // for action events to override
        // virtual bool checkReadyForNextState();

        static void initFonts();

        virtual ~Element();
    protected:
        //mainly for elements in views, subclass does not need to use (can consider itself always enabled)
        bool isEnabled;

        std::string name; //identifier

        sf::RenderWindow* window;
        static sf::Font* font;
};

#endif