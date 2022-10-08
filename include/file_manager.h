#ifndef FILE_MANAGER
#define FILE_MANAGER

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "avl/avl_tree.h"
#include "recipe.h"

class FileManager {
  public:
    FileManager(std::string ingredientPath, std::string recipePath, AVLTree<Ingredient*>* ingredients, std::vector<Recipe*>* recipes);
    ~FileManager();
  private:
    std::string ingredientPath, recipePath;
};

#endif