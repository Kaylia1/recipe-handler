#ifndef RECIPE
#define RECIPE

#include "ingredient.h"

class Recipe : public FoodComponent {
  public:
    struct PortionedIngredient {
      FoodComponent* ingredient; // pointer to ingredient, shared by file_manager
      std::pair<double,std::string> amt; // amt and unit pair
    };

    Recipe();
    void setServings(double servings);
    void addIngredient(PortionedIngredient newPortionedIngredient);
    void appendStep(std::string nextStep);
    void appendNote(std::string nextNote);
    void calcStdCost();

    //int addStep
    //int addNote
    //int permScale

    virtual double getCost(std::pair<double, std::string> desiredAmt); //for recipes that act as ingredients

    virtual ~Recipe();
  private:
    double stdServings;
    std::vector<PortionedIngredient> parts;
    std::vector<std::string> steps;
    std::vector<std::string> notes;
};

#endif