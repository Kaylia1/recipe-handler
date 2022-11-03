#ifndef RECIPE
#define RECIPE

#include "whole_ingredient.h"
#include "divisible_ingredient.h"
#include "utility/element.h"

class Recipe : public FoodComponent {
    public:
        struct PortionedIngredient {
            FoodComponent* ingredient; // pointer to ingredient, shared by file_manager
            std::pair<double,std::string> amt; // amt and unit pair
        };

        Recipe(std::string name);
        void setServings(double servings);
        void addIngredient(PortionedIngredient nextPortionedIngredient);
        void appendStep(std::string nextStep);
        void appendNote(std::string nextNote);
        double calcStdCost();

        //TODO print function passing in ofstream rather than return ptr
        double getStdServings();
        const std::vector<PortionedIngredient>* getIngredients();
        const std::vector<std::string>* getSteps();
        const std::vector<std::string>* getNotes();

        virtual double getCost(std::pair<double, std::string> desiredAmt); //for recipes that act as ingredients

        // void draw();

        virtual ~Recipe();
    private:

        double stdServings;
        std::vector<PortionedIngredient> parts;
        std::vector<std::string> steps;
        std::vector<std::string> notes;

        // Element *drawElement;
};

#endif