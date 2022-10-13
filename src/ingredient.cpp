#include "../include/ingredient.h"

Ingredient::Ingredient(FileManager* saveData){
    this->saveData = saveData;
    cost = -1.0;
    amt = -1.0;
    volUnit = UNKNOWN_UNIT;
    mass = -1.0;
    massUnit = UNKNOWN_UNIT;
}

void Ingredient::setCost(double cost){ this->cost = cost; }
void Ingredient::setAmt(double amt){ this->amt = amt; }
void Ingredient::setVolUnit(std::string volUnit){ this->volUnit = volUnit; }
void Ingredient::setMass(double mass){ this->mass = mass; }
void Ingredient::setMassUnit(std::string massUnit){ this->massUnit = massUnit; }

void Ingredient::addAltIngredient(std::string ingredientKey){
    altIngredients.push_back(ingredientKey);
}

double Ingredient::getCost(){
    return cost;
}

double Ingredient::getAmt(){
    return amt;
}

std::string Ingredient::getVolUnit(){
    return volUnit;
}

double Ingredient::getMass(){
    return mass;
}

std::string Ingredient::getMassUnit() {
    return massUnit;
}

std::vector<std::string>* Ingredient::getAlts(){
    return &altIngredients;
}

double Ingredient::getCost(std::pair<double, std::string> desiredAmt){
    
    return -1.0;
}

Ingredient::~Ingredient(){}