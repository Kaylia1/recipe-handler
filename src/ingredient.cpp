#include "../include/ingredient.h"

Ingredient::Ingredient(FileManager* saveData){
    this->saveData = saveData;
}

void Ingredient::setCost(double cost){ this->cost = cost; }
void Ingredient::setAmt(double amt){ this->amt = amt; }
void Ingredient::setVolUnit(std::string volUnit){ this->volUnit = volUnit; }
void Ingredient::setMass(double mass){ this->mass = mass; }
void Ingredient::setMassUnit(std::string massUnit){ this->massUnit = massUnit; }

void Ingredient::addAltIngredient(std::string ingredientKey){
    altIngredients.push_back(ingredientKey);
}

double Ingredient::getCost(std::pair<double, std::string> desiredAmt){
    
    return -1.0;
}

Ingredient::~Ingredient(){}