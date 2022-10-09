#include "../include/file_manager.h"

FileManager::FileManager(std::string ingredientPath, std::string recipePath) {
    this->ingredientPath = ingredientPath;
    this->recipePath = recipePath;
}
/**
 * ingredient format:
 * [name] [cost] [amt] [unit] [(opt) weight] [(opt) weight unit] [(opt) list of alt ingredients]
 * */
void FileManager::loadIngredients(){
    std::ifstream ingredientFile;
    std::string curLine;
    std::string curStrBuff;
    double curDoubleBuff;
    Ingredient* tempIngredient;
    std::string tempKey;

    ingredientFile.open (ingredientPath);
    if (ingredientFile.is_open()) {
        while(std::getline(ingredientFile,curLine)){
            tempIngredient = new Ingredient();

            std::stringstream ss(curLine);
            ss >> tempKey;
            ss >> curDoubleBuff;
            tempIngredient->setCost(curDoubleBuff);
            ss >> curDoubleBuff;
            tempIngredient->setAmt(curDoubleBuff);
            ss >> curStrBuff;
            tempIngredient->setVolUnit(curStrBuff);

            // mass is known
            if(ss >> curStrBuff) {
                std::stringstream checkDouble(curStrBuff);
                checkDouble >> curDoubleBuff;
                if(!checkDouble.fail()) {
                    tempIngredient->setMass(curDoubleBuff);
                    ss >> curStrBuff;
                    tempIngredient->setMassUnit(curStrBuff);
                }

                //alt ingredients
                while(ss >> curStrBuff) {
                    tempIngredient->addAltIngredient(curStrBuff);
                }
                
            } // no more in ss
            allIngredients.insert(std::pair<std::string, Ingredient*>(tempKey, tempIngredient));
        }

        // TODO iterate one more time to check alt ingredients exist
        ingredientFile.close();
    } else {
        printf("ERROR: loadIngredients failed, possibly path not valid.\n");
    }

}

/**
 * recipe format
 * */
void FileManager::loadRecipes(){

}

FileManager::~FileManager(){
    
}