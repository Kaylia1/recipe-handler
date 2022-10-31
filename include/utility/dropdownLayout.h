#ifndef DD_LAYOUT
#define DD_LAYOUT

//todo move win ctrl out of util
//pass in layout to filemanager, pass filemanager to winctrl, add genRecipes/ingredients elements to filemanager
//platable var for whether or not to show
//actual showing of recipe/ingredient
//make search work

#include <vector>

#include "button.hpp"
#include "element.h"

class DropdownLayout : public Element{
    public:
        static const int OPTION_HEIGHT;

        DropdownLayout(std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax);
        DropdownLayout(std::string name, sf::RenderWindow* window, int xMin, int yMin, int xMax, std::string preloadedOptions[], int numLoad);
        void addOption(std::string opt);
        std::string getCurOption();

        virtual void draw();
        virtual void update(sf::Event* event);

        virtual ~DropdownLayout();
    private:
        void select(Button<DropdownLayout>* id);    
        std::vector<Button<DropdownLayout>> options;
        std::string selectedOption;

        int xMin, yMin, xMax;
};

#endif