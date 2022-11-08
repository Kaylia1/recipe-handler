#ifndef SCROLLBAR_LAYOUT
#define SCROLLBAR_LAYOUT

#include "element.h"
// #include 
// #include 

/**
 * Ratio of scrollbar height : scrollbar space is same as show size : actual size
*/
class ScrollbarLayout : public Element {
    public:

        static const int SCROLL_BAR_WIDTH;
        //currently defaults to right side

        ScrollbarLayout(std::string name, sf::RenderWindow* window, int windowWidth, int windowHeight, int xMin, int yMin, int width, int height, int realHeight);

        //turns relative coords into abs coords
        //warning does not check if element goes out of window size
        float translateInnerElementX(int xRelative);
        float translateInnerElementY(int yRelative);
        void addInnerElement(Element *element, bool delWhenDone = true);
        //TODO add functionality for relative coords

        virtual void draw();
        virtual void update(sf::Event* event, int mouseX, int mouseY);
        virtual void update(); //once

        virtual ~ScrollbarLayout();
    private:
        bool checkInBounds(int x, int y);
        bool checkInWinBounds(int x, int y);
        void updateInnerElementOffsets();

        bool isDragging;

        int windowWidth, windowHeight;

        //window coords
        int xMin, yMin;

        int showYMin; // relative to scrollbar coords, sorta like offset of scrollbar location
        int mouseDragOffset;

        int actualLayoutSize;
        int showLayoutSize;

        int scrollbarHeight;

        int width;

        std::vector<std::pair<Element*, bool>> innerElements; //vector of inner element ptrs

        sf::RectangleShape *scrollbar, *innerBackground;
        sf::View* view;
};

#endif