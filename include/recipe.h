#ifndef RECIPE
#define RECIPE

#include "ingredient.h"

class Recipe : public FoodComponent {
  public:
    struct PortionedIngredient {
        FoodComponent ingredient;
        double amount;
        std::string unit;
    };

    Recipe();
    bool addIngredient(PortionedIngredient* newIngredient);
    double calcCost(double desiredServings);
    ~Recipe();
  private:
    PortionedIngredient* components; // array of ingredients in a recipe
    std::string* steps; // array of string steps
    double servings;
};

#endif