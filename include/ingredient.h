#ifndef INGREDIENT
#define INGREDIENT

#include "food_component.h"

class Ingredient : public FoodComponent {
  public:
    Ingredient();
    bool addAlt(FoodComponent*);
    ~Ingredient();
  private:
    // possible future: struct BuyOpt {Cost, Bulk, Store}
    double cost; // dollars
    double purchaseSize; // bulk buy at store
    std::string unit; // unit of measurement
    FoodComponent* alternatives;
    // std::string store; // currently unsupported
};

#endif