#include "../include/wholeIngredient.h"

WholeIngredient::WholeIngredient(std::string name, double cost, double amt) : FoodComponent(name){
    this->cost = cost;
    this->amt = amt;
}

void WholeIngredient::setCost(double cost){ this->cost = cost; }
void WholeIngredient::setAmt(double amt){ this->amt = amt; }

void WholeIngredient::addAltIngredient(std::string ingredientKey){
    altIngredients.push_back(ingredientKey);
}

double WholeIngredient::getCost(){
    return cost;
}

double WholeIngredient::getAmt(){
    return amt;
}

//todo have a writeToFile method so you don't do below
std::vector<std::string>* WholeIngredient::getAlts(){
    return &altIngredients;
}

double WholeIngredient::getCost(std::pair<double, std::string> desiredAmt){
    if (desiredAmt.second.compare(WHOLE_UNIT) != 0){
        printf("WARNING tried to access whole ingredient as splittable\n");
        return -1.0;
    } else {
        return cost / amt * desiredAmt.first;
    }
}

WholeIngredient::~WholeIngredient(){}