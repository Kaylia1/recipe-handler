#ifndef W_INGREDIENT
#define W_INGREDIENT

#include <vector>

#include "foodComponent.h"
// #include "recipe.h"

class FileManager;

class WholeIngredient : public FoodComponent {
    public:
        WholeIngredient(std::string name, double cost, double amt);
        void setCost(double cost);
        void setAmt(double amt);
        void addAltIngredient(std::string ingredientKey);

        double getCost();
        double getAmt();
        std::vector<std::string>* getAlts();
        virtual double getCost(std::pair<double, std::string> desiredAmt);

        virtual ~WholeIngredient();
    protected:
        double cost, amt;

        std::vector<std::string> altIngredients; // vector of keys to other ingredients

};

#endif