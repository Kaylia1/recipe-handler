#include "../../include/utility/scrollbarLayout.h"

const int ScrollbarLayout::SCROLL_BAR_WIDTH = 10;

ScrollbarLayout::ScrollbarLayout(std::string name, sf::RenderWindow* window, int windowWidth, int windowHeight, int xMin, int yMin, int width, int height, int realHeight) : Element(name, window){

    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    this->xMin = xMin;
    this->yMin = yMin;

    // actualLayoutSize = height;
    actualLayoutSize = realHeight;
    showLayoutSize = height;
    showYMin = 0;
    this->width = width;

    isDragging = false;

    scrollbarHeight = showLayoutSize * showLayoutSize / actualLayoutSize;
    // printf("creating new, scrollbar height is: %d\n", scrollbarHeight);

    //scrollbar rect
    scrollbar = new sf::RectangleShape(sf::Vector2f((float) (SCROLL_BAR_WIDTH), (float)(scrollbarHeight)));
    scrollbar->setFillColor(sf::Color(75,75,75));
    scrollbar->setPosition(sf::Vector2f((float) (xMin + width - SCROLL_BAR_WIDTH), (float) (yMin + showYMin)));

    innerBackground = new sf::RectangleShape(sf::Vector2f((float)width - SCROLL_BAR_WIDTH, (float)actualLayoutSize));
    innerBackground->setFillColor(sf::Color(240, 240, 240));
    innerBackground->setPosition(sf::Vector2f((-width - SCROLL_BAR_WIDTH) / 2.0f, -showLayoutSize / 2.0f));

    view = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(width - SCROLL_BAR_WIDTH, height));
}

//because drawing at 0,0 in viewport is center rather than top left
float ScrollbarLayout::translateInnerElementX(int xRelative) {
    if(xRelative >= width) {
        printf("Warning: would add offscreen element to Scrollbar\n");
    }
    return xRelative - width / 2.0f;
}

float ScrollbarLayout::translateInnerElementY(int yRelative) {
    // if(yRelative >= actualLayoutSize) {
    //     actualLayoutSize = yRelative; // todo + element height
    //     scrollbarHeight = showLayoutSize / actualLayoutSize;
    //     scrollbar->setSize(sf::Vector2f((float) (SCROLL_BAR_WIDTH), (float)(scrollbarHeight)));
    // }
    return yRelative - showLayoutSize / 2.0f;
}

void ScrollbarLayout::addInnerElement(Element* element) {
    innerElements.push_back(element);
}

void ScrollbarLayout::draw() {
    if(isDragging) {
        scrollbar->setFillColor(sf::Color(50,50,50));
    }
    scrollbar->setPosition(sf::Vector2f((float) (xMin + width - SCROLL_BAR_WIDTH), (float) (yMin + showYMin)));

    window->draw(*scrollbar);

    //ratio is width : windowWidth    
    // view->setViewport(sf::FloatRect(windowWidth / 2.0f - (width-SCROLL_BAR_WIDTH) / 2.0f, windowHeight / 2.0f - showLayoutSize / 2.0f, width / windowWidth, showLayoutSize / windowHeight))
    // view->setSize(0.5f, 0.5f);
    // printf("%f \n", showLayoutSize * 1.0f / windowHeight);
    view->setViewport(sf::FloatRect(xMin * 1.0f / windowWidth, yMin * 1.0f / windowHeight, width * 1.0f / windowWidth, showLayoutSize * 1.0f / windowHeight));
    
    window->setView(*view);
    window->draw(*innerBackground);
    for(unsigned long i = 0; i < innerElements.size(); i++) {
        // printf("drawing inner?\n");
        innerElements[i]->draw();
    }
    window->setView(window->getDefaultView());
}

void ScrollbarLayout::update(sf::Event* event, int mouseX, int mouseY) {

    // printf("checkin %d %d\n", xMin, width);

    if(event->type == sf::Event::MouseButtonReleased){
        // printf("released!\n");
        isDragging = false;
        update();
    } else if(event->type == sf::Event::MouseButtonPressed){
        
        isDragging = checkInBounds(mouseX, mouseY);
        mouseDragOffset = mouseY - yMin - showYMin;
        
        
    }

    bool valid = checkInWinBounds(mouseX, mouseY);

    float tx = mouseX - xMin - width / 2.0f;
    float ty = mouseY - yMin - showLayoutSize / 2.0f + showYMin * 1.0f * actualLayoutSize / showLayoutSize;
    
    for(unsigned long i = 0; i < innerElements.size(); i++) {
        innerElements[i]->setEnabled(valid);
        innerElements[i]->update(event, tx, ty);
    }
}

void ScrollbarLayout::update() {
    // printf("norm update!\n");
    if(isDragging) {
        // printf("dragging %d\n", showYMin);
        showYMin = sf::Mouse::getPosition(*window).y - yMin - mouseDragOffset;

        if(showYMin > showLayoutSize - scrollbarHeight) {
            showYMin = showLayoutSize - scrollbarHeight;
        } else if (showYMin < 0) {
            showYMin = 0;
        }
        view->setCenter(0.0f, showYMin*1.0f*actualLayoutSize/showLayoutSize);// + actualLayoutSize / 2.0f);
    }
    // if(checkInWinBounds(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)) {
    for(unsigned long i = 0; i < innerElements.size(); i++) {
        innerElements[i]->update();
    }
    // }
}

void ScrollbarLayout::updateInnerElementOffsets(){

}

bool ScrollbarLayout::checkInBounds(int x, int y) {
    return x >= (xMin + width - SCROLL_BAR_WIDTH) && x <= (xMin + width) && y >= yMin + showYMin && y <= yMin + scrollbarHeight + showYMin;
}

bool ScrollbarLayout::checkInWinBounds(int x, int y) {
    return x >= xMin && x <= (xMin + width) && y >= yMin && y <= yMin + showLayoutSize;
}

ScrollbarLayout::~ScrollbarLayout(){
    delete innerBackground;
    delete scrollbar;
    delete view;

    //scrollbar layout trusted to manage inner elements, assumed it is not shared anywhere else
    for(unsigned long i = 0; i < innerElements.size(); i++) {
        delete innerElements[i];
    }
}