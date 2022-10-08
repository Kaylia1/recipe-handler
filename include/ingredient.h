#ifndef INGREDIENT
#define INGREDIENT

#include "food_component.h"

class Ingredient : public FoodComponent {
  public:
    Ingredient();

    virtual double getCost(std::pair<double, std::string> desiredAmt);

    ~Ingredient();
  private:
    std::string name;
};

#endif