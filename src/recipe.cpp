#include "../include/recipe.h"

Recipe::Recipe(std::string name) : FoodComponent(name){
    stdServings = -1.0;
}

void Recipe::setServings(double servings){
    stdServings = servings;
}
// allows duplicate ingredients... TODO consider combining
void Recipe::addIngredient(PortionedIngredient nextPortionedIngredient){
    parts.push_back(nextPortionedIngredient);
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

double Recipe::getStdServings() {return stdServings;}
std::vector<Recipe::PortionedIngredient>* Recipe::getIngredients() {return &parts;}
std::vector<std::string>* Recipe::getSteps() {return &steps;}
std::vector<std::string>* Recipe::getNotes() {return &notes;}

// for recipes that act as components to other recipes ie pie crust
double Recipe::getCost(std::pair<double, std::string> desiredAmt){
    return -1.0;
}

Recipe::~Recipe(){}