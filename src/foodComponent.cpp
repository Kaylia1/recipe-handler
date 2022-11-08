#include "../include/foodComponent.h"

FoodComponent::FoodComponent(std::string name) {
    this->name = name;
}

std::string FoodComponent::getName() {
    return name;
}