#ifndef RECIPE
#define RECIPE

#include "ingredient.h"

class Recipe : public FoodComponent {
  public:
    struct PortionedIngredient {
        FoodComponent* ingredient;
        std::pair<double,std::string> amt;
    };

    Recipe();

    virtual double getCost(std::pair<double, std::string> desiredAmt); //for recipes that act as ingredients

    ~Recipe();
  private:

    std::string name;
};

#endif