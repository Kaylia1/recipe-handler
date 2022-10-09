#include "../include/recipe.h"

Recipe::Recipe(){
    stdServings = -1.0;
}

void Recipe::setServings(double servings){

}
void Recipe::addIngredient(PortionedIngredient newPortionedIngredient){
    
}
void Recipe::appendStep(std::string nextStep){
    steps.push_back(nextStep);
}
void Recipe::appendNote(std::string nextNote){
    notes.push_back(nextNote);
}
void Recipe::calcStdCost(){
    //TODO
}

// for recipes that act as components to other recipes ie pie crust
double Recipe::getCost(std::pair<double, std::string> desiredAmt){
    return -1.0;
}

Recipe::~Recipe(){}