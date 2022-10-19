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
double Recipe::calcStdCost(){
    double totalCost = 0.0;
    for(unsigned long i = 0; i < parts.size(); i++) {
        totalCost += parts[i].ingredient->getCost(parts[i].amt);
    }
    return totalCost;
}

double Recipe::getStdServings() {return stdServings;}
std::vector<Recipe::PortionedIngredient>* Recipe::getIngredients() {return &parts;}
std::vector<std::string>* Recipe::getSteps() {return &steps;}
std::vector<std::string>* Recipe::getNotes() {return &notes;}

// for recipes that act as components to other recipes ie pie crust
/** 
 * returns negative number if:
 * - stdServings not set & requested servings unit
 * - requested unit other than whole or servings
 **/
double Recipe::getCost(std::pair<double, std::string> desiredAmt){
    if(desiredAmt.second.compare(SERVING_UNIT) == 0) {
        return calcStdCost() * desiredAmt.first / stdServings;
    } else if (desiredAmt.second.compare(WHOLE_UNIT) == 0){
        return calcStdCost() * desiredAmt.first;
    } else {
        printf("invalid unit %s in recipe getCost, please use servings or whole\n", desiredAmt.second.c_str());
        return -1.0;
    }
}

Recipe::~Recipe(){}