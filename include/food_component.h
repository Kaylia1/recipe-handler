#ifndef FOOD_CMP
#define FOOD_CMP

#include <map>

// TODO put inside class as static const
// convert A to B: A*cupEq["B"]/cupEq["A"]
const std::map<std::string, double> cupEq = {
    {"tsp", 48.0},
    {"tbsp", 16.0},
    {"floz", 8.0},
    {"cup", 1.0},
    {"pint", 1.0/2.0},
    {"quart", 1.0/4.0},
    {"gallon", 1.0/16.0},

    {"mL", 250.0}
};

const std::map<std::string, double> lbEq = {
    {"oz", 8.0},
    {"lb", 1.0},

    {"g", 450.0}
};

// TODO make abstract class
class FoodComponent {
  public:
    bool scale(double ratio);
};

#endif