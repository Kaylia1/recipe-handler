#include "../include/recipeDisplay.h"

//note: overloading button, but also using itself as a generic in button? technically don't need the generic...

RecipeDisplay::RecipeDisplay(sf::RenderWindow *window, Recipe* recipe, int xMin, int yMin, int width) : Element(recipe->getName(), window){
    this->recipe = recipe;
    isExpanded = false;
    justChanged = none;

    this->xMin = xMin;
    this->yMin = yMin;
    this->xMax = xMin + width;
    this->yMax = yMin + TITLE_HEIGHT;

    display = new Button<RecipeDisplay>(this, &RecipeDisplay::activate, recipe->getName(), window, xMin, yMin, xMax, yMax);

    expandedSize = TITLE_HEIGHT *
        (5 + //5 for name, servings/cost, ingredients, steps, notes
        recipe->getIngredients()->size() +
        recipe->getSteps()->size() +
        recipe->getNotes()->size());
    // printf("expanded size for %s is %d\n", recipe->getName().c_str(), expandedSize);

    std::stringstream newTitle;
    newTitle << recipe->getName() << "\nServings: " << recipe->getStdServings()
        << "\nIngredients:\n" << listIngredients()
        << "Steps:\n" << listSteps()
        << "Notes:\n" << listNotes();
    expandedText = newTitle.str();
}

void RecipeDisplay::draw(){
    display->draw();
}

void RecipeDisplay::update(sf::Event *event, int mouseX, int mouseY) {
    display->update(event, mouseX, mouseY);
}

void RecipeDisplay::shiftYVal(int offset) {
    yMin += offset;
    yMax += offset;
    display->changeSize(xMin, yMin, xMax, yMax);
}

int RecipeDisplay::getMinY() {
    return yMin;
}

//id == display
void RecipeDisplay::activate(Button<RecipeDisplay>* id) {
    // printf("activating!\n");

    if(!isExpanded) { //expand
        yMax = yMin + expandedSize;
        id->changeSize(xMin, yMin, xMax, yMax);
        id->setTitle(expandedText);
        justChanged = expanded;
        isExpanded = true;
    } else { //minimize
        // printf("minimizing!\n");
        yMax = yMin + TITLE_HEIGHT;
        id->changeSize(xMin, yMin, xMax, yMax);
        id->setTitle(recipe->getName());
        justChanged = minimized;
        isExpanded = false;
    }
}

double RecipeDisplay::getExtraHeight() {
    StateChange lastChange = getChanged();
    switch(lastChange){
        case expanded:
            return expandedSize - TITLE_HEIGHT;
        case minimized:
            return - (expandedSize - TITLE_HEIGHT);
        case none:
            return 0;
    }
    // return (yMax - yMin) - TITLE_HEIGHT;
}

//returns state then clears to none ea call
RecipeDisplay::StateChange RecipeDisplay::getChanged() {
    if(justChanged != StateChange::none){
        StateChange retVal = justChanged;
        justChanged = none;
        return retVal;
    }
    return justChanged;
}

std::string RecipeDisplay::listIngredients() {
    std::stringstream list;
    const std::vector<Recipe::PortionedIngredient>* allIngredients = recipe->getIngredients();
    for(unsigned long i = 0; i<allIngredients->size(); i++) {
        list << allIngredients->at(i).amt.first << " ";
        list << allIngredients->at(i).amt.second << " ";
        list << allIngredients->at(i).ingredient->getName();
        list << "\n";
    }
    return list.str();
}

std::string RecipeDisplay::listSteps() {
    std::string list;
    const std::vector<std::string>* allSteps = recipe->getSteps();
    for(unsigned long i = 0; i<allSteps->size(); i++) {
        list += allSteps->at(i) + "\n";
    }
    return list;
}

std::string RecipeDisplay::listNotes() {
    std::string list;
    const std::vector<std::string>* allNotes = recipe->getNotes();
    for(unsigned long i = 0; i<allNotes->size(); i++) {
        list += allNotes->at(i) + "\n";
    }
    return list;
}

RecipeDisplay::~RecipeDisplay(){
    delete display;
}