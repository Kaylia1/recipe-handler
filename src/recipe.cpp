#include "../include/recipe.h"

Recipe::Recipe(std::string name) : FoodComponent(name){
    // drawElement = nullptr;
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
    if(nextStep.size() > MAX_LINE_LEN) {
        for(int i = 0; i < nextStep.size(); i+= MAX_LINE_LEN) {
            //if last str partition is longer, substr gives as many chars as exist
            steps.push_back(nextStep.substr(i, MAX_LINE_LEN));
        }
    } else {
        steps.push_back(nextStep);
    }
}
void Recipe::appendNote(std::string nextNote){
    if(nextNote.size() > MAX_LINE_LEN) {
        for(int i = 0; i < nextNote.size(); i+= MAX_LINE_LEN) {
            //if last str partition is longer, substr gives as many chars as exist
            notes.push_back(nextNote.substr(i, MAX_LINE_LEN));
        }
    } else {
        notes.push_back(nextNote);
    }
}
double Recipe::calcStdCost(){
    double totalCost = 0.0;
    for(unsigned long i = 0; i < parts.size(); i++) {
        totalCost += parts[i].ingredient->getCost(parts[i].amt);
    }
    return totalCost;
}

double Recipe::getStdServings() {return stdServings;}
const std::vector<Recipe::PortionedIngredient>* Recipe::getIngredients() {return &parts;}
const std::vector<std::string>* Recipe::getSteps() {return &steps;}
const std::vector<std::string>* Recipe::getNotes() {return &notes;}

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

// void Recipe::draw() {
//     if(drawElement != nullptr) {
//         drawElement->draw();
//     }
// }

Recipe::~Recipe(){}