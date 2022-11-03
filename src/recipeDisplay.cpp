#include "../include/recipeDisplay.h"

//note: overloading button, but also using itself as a generic in button? technically don't need the generic...

RecipeDisplay::RecipeDisplay(sf::RenderWindow *window, Recipe* recipe, int xMin, int yMin, int width) : Button<RecipeDisplay>(this, &RecipeDisplay::activate, recipe->getName(), window, xMin, yMin, xMin + width, yMin + TITLE_HEIGHT) {
    this->recipe = recipe;
    isExpanded = false;
}

// void RecipeDisplay::update(sf::Event *event, int mouseX, int mouseY) {
//     isHoveredOver = checkInBounds(mouseX, mouseY);

//     if(isEnabled && event->type == sf::Event::MouseButtonPressed && isHoveredOver){
//         isJustPressed = isHoveredOver; //updates every mouse click

//         if (actionable != nullptr) {
//             (actionable->*classAction)(this);
//         } else if (action != nullptr) {
//             (*action)(this);
//         } else {
//             printf("Warning: nullptr action passed to recipe display\n");
//         }

//     }
// }

void RecipeDisplay::activate(Button<RecipeDisplay>* id) {

    if(!isExpanded) { //expand
        unsigned long approxSize = 20 * 
            (5 + //5 for name, servings/cost, ingredients, steps, notes
            recipe->getIngredients()->size() +
            recipe->getSteps()->size() +
            recipe->getNotes()->size());
        
        xMax += approxSize;

        std::stringstream newTitle;
        newTitle << name << "\nServings: " << recipe->getStdServings()
            << "\nIngredients:\n" << listIngredients()
            << "\nSteps:\n" << listSteps()
            << "\nNotes:\n" << listNotes();

        title->setString(newTitle.str());
    } else { //minimize
        xMax = xMin + TITLE_HEIGHT;
    }
}

std::string RecipeDisplay::listIngredients() {
    std::stringstream list;
    const std::vector<Recipe::PortionedIngredient>* allIngredients = recipe->getIngredients();
    for(unsigned long i = 0; i<allIngredients->size(); i++) {
        list << allIngredients->at(i).amt.first << " ";
        list << allIngredients->at(i).amt.second << " ";
        list << allIngredients->at(i).ingredient->getName();
    }
    return list.str();
}

std::string RecipeDisplay::listSteps() {
    std::string list;
    const std::vector<std::string>* allSteps = recipe->getSteps();
    for(unsigned long i = 0; i<allSteps->size(); i++) {
        list += allSteps->at(i);
    }
    return list;
}

std::string RecipeDisplay::listNotes() {
    std::string list;
    const std::vector<std::string>* allNotes = recipe->getNotes();
    for(unsigned long i = 0; i<allNotes->size(); i++) {
        list += allNotes->at(i);
    }
    return list;
}

RecipeDisplay::~RecipeDisplay(){

}