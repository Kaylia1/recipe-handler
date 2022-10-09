#ifndef INGREDIENT
#define INGREDIENT

#include <vector>

#include "food_component.h"
#include "file_manager.h"
#include "recipe.h"

class FileManager;

class Ingredient : public FoodComponent {
  public:
    Ingredient(FileManager* saveData);
    void setCost(double cost);
    void setAmt(double amt);
    void setVolUnit(std::string volUnit);
    void setMass(double mass);
    void setMassUnit(std::string massUnit);
    void addAltIngredient(std::string ingredientKey);

    virtual double getCost(std::pair<double, std::string> desiredAmt);


    virtual ~Ingredient();
  private:
    FileManager* saveData;

    double cost, amt, mass;
    std::string volUnit, massUnit;

    std::vector<std::string> altIngredients; // vector of keys to other ingredients

};

#endif