#ifndef D_INGREDIENT
#define D_INGREDIENT

#include <vector>

#include "wholeIngredient.h"
// #include "recipe.h"

class WholeIngredient;

class DivisibleIngredient : public WholeIngredient {
  public:
    DivisibleIngredient(std::string name, double cost, double amt, std::string volUnit);
    void setVolUnit(std::string volUnit);
    void setMass(double mass);
    void setMassUnit(std::string massUnit);

    std::string getVolUnit();
    double getMass();
    std::string getMassUnit();
    virtual double getCost(std::pair<double, std::string> desiredAmt);


    virtual ~DivisibleIngredient();
  private:

    double mass; //amt is volume
    std::string volUnit, massUnit;

};

#endif