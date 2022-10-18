#include "../include/food_component.h"

FoodComponent::FoodComponent(std::string name) {
    this->name = name;
}

std::string FoodComponent::getName() {
    return name;
}