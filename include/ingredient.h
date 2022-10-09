#ifndef INGREDIENT
#define INGREDIENT

#include "food_component.h"

class Ingredient : public FoodComponent {
  public:
    Ingredient();
    void setCost(double cost);
    void setAmt(double amt);
    void setVolUnit(std::string volUnit);
    void setMass(double mass);
    void setMassUnit(std::string massUnit);
    void addAltIngredient(std::string ingredientKey);




    virtual double getCost(std::pair<double, std::string> desiredAmt);


    ~Ingredient();
  private:
    std::string name;
};

#endif