#include "../include/divisible_ingredient.h"

DivisibleIngredient::DivisibleIngredient(std::string name, double cost, double amt, std::string volUnit)
    : WholeIngredient(name, cost, amt){

    this->volUnit = volUnit;
    mass = -1.0;
    massUnit = UNKNOWN_UNIT;
}

void DivisibleIngredient::setVolUnit(std::string volUnit){ this->volUnit = volUnit; }
void DivisibleIngredient::setMass(double mass){ this->mass = mass; }
void DivisibleIngredient::setMassUnit(std::string massUnit){ this->massUnit = massUnit; }

std::string DivisibleIngredient::getVolUnit(){
    return volUnit;
}

double DivisibleIngredient::getMass(){
    return mass;
}

std::string DivisibleIngredient::getMassUnit() {
    return massUnit;
}

double DivisibleIngredient::getCost(std::pair<double, std::string> desiredAmt){
    if (CUP_EQ.count(desiredAmt.second) > 0) { // volume was given
        // convert a of unit A to b of unit B
        double costPerCup = cost / (amt / CUP_EQ.at(volUnit));
        double amtInCups = desiredAmt.first / CUP_EQ.at(desiredAmt.second);
        return costPerCup * amtInCups;
    } else if (LB_EQ.count(desiredAmt.second) > 0) { // mass was given
        if (massUnit.compare(UNKNOWN_UNIT) == 0) {
            printf("WARNING tried to get cost in mass, but mass or ingredient %s unknown\n", name.c_str());
            return -1.0;
        } else {
            double costPerLb = cost / (amt / LB_EQ.at(volUnit));
            double amtInLbs = desiredAmt.first / LB_EQ.at(desiredAmt.second);
            return costPerLb * amtInLbs;
        }
    } else {
        printf("invalid unit %s given to getCost\n", desiredAmt.second.c_str());
        return -1.0;
    }
}

DivisibleIngredient::~DivisibleIngredient(){}