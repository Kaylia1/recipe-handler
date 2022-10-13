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
    int lineNum = 0;

    std::ifstream ingredientFile;
    std::string curLine;
    std::string curStrBuff;
    double curDoubleBuff;
    Ingredient* tempIngredient;
    std::string tempKey;

    ingredientFile.open (ingredientPath);
    if (ingredientFile.is_open()) {

        //for each line
        while(std::getline(ingredientFile,curLine)){
            lineNum++;
            
            std::stringstream ss(curLine);
            ss >> tempKey;
            if(allIngredients.count(tempKey) > 0) {
                printf("WARNING duplicate ingredient name at line %d in file, second ignored.\n", lineNum);
                continue;
            }
            tempIngredient = new Ingredient(this);
            ss >> curDoubleBuff;
            tempIngredient->setCost(curDoubleBuff);
            ss >> curDoubleBuff;
            tempIngredient->setAmt(curDoubleBuff);
            ss >> curStrBuff;
            tempIngredient->setVolUnit(curStrBuff);

            // mass is known
            if(ss >> curStrBuff) {
                //check if double, if so then weight info known
                std::stringstream checkDouble(curStrBuff);
                checkDouble >> curDoubleBuff;
                if(!checkDouble.fail()) {
                    tempIngredient->setMass(curDoubleBuff);
                    ss >> curStrBuff;
                    tempIngredient->setMassUnit(curStrBuff);
                }

                //alt ingredients
                do { //curStrBuff read earlier
                    tempIngredient->addAltIngredient(curStrBuff);
                } while(ss >> curStrBuff);
                
            } // no more in ss
            allIngredients.insert(std::pair<std::string, Ingredient*>(tempKey, tempIngredient));
        }

        // note assuming alt ingredients exist

        ingredientFile.close();
    } else {
        printf("ERROR: loadIngredients failed, possibly path not valid.\n");
    }

}

/**
 * recipe format:
 * [recipe name]
 * [approx servings ie whole cookies or # cake slices. -1 if unknown]
 * ingredients
 * [amt] [unit] [food component name]
 * [amt] [unit] [food component2 name] etc
 * steps
 * [instruction 1]
 * [instruction 2] etc
 * notes
 * [note 1]
 * [note 2] etc
 * -----
 * let ingredient class handle volume/mass conversion
 * */
void FileManager::loadRecipes(){
    int recipeNum = 0;

    std::string curLine;
    std::string recipeName;
    double curDoubleBuff;
    std::string curStrBuff;
    Recipe* tempRecipe;
    Recipe::PortionedIngredient tempPortionedIngredient;

    std::ifstream recipeFile;

    recipeFile.open(recipePath);
    if (recipeFile.is_open()) {
        //for each recipe
        while(recipeFile.peek() != EOF) {
            recipeNum++;

            if(!std::getline(recipeFile, recipeName)){ // TODO do check if dup key here
                printf("WARNING file still open but no more recipes to read by %d\n", recipeNum);
                return;
            }
            if(allRecipes.count(recipeName) > 0) { // key already exists, fail
                printf("WARNING %s duplicate key so recipe %d failed to add. Did you edit the file format?\n", recipeName.c_str(), recipeNum);
                return;
            }

            tempRecipe = new Recipe();

            //servings
            if(!std::getline(recipeFile, curStrBuff)){
                printf("WARNING file ended prematurely on getting servings on recipe %d\n", recipeNum);
                delete tempRecipe;
                return;
            }
            std::stringstream checkServingsIsDb(curStrBuff);
            checkServingsIsDb >> curDoubleBuff;
            tempRecipe->setServings(curDoubleBuff);

            // get "ingredients"
            if(!std::getline(recipeFile, curStrBuff)){
                printf("WARNING ingredients keyword not contained cause file ended prematurely %d\n", recipeNum);
                delete tempRecipe;
                return;
            }

            // ingredient line
            while(std::getline(recipeFile, curStrBuff) && curStrBuff.compare("steps") != 0){
                std::stringstream ingredientSS(curStrBuff);
                ingredientSS >> tempPortionedIngredient.amt.first;
                ingredientSS >> tempPortionedIngredient.amt.second;
                ingredientSS >> curStrBuff;

                // Assumes that there is not a recipe and ingredient by the same name, but if there is, would take ingredient
                if(allIngredients.count(curStrBuff) <= 0) {
                    if(allRecipes.count(curStrBuff) <= 0) {
                        //TODO currently replaces unknown ingredient with 0xfffff if recipe loaded and written to file
                        printf("ERROR tried to add invalid ingredient in recipe %d under name %s\n", recipeNum, curStrBuff.c_str());
                    } else { //is a recipe type
                        tempPortionedIngredient.ingredient = (FoodComponent*) allRecipes[curStrBuff];
                    }
                } else { //is an ingredient type
                    tempPortionedIngredient.ingredient = (FoodComponent*) allIngredients[curStrBuff];
                }

                // TODO should send string as key
                tempRecipe->addIngredient(tempPortionedIngredient); // not a ptr, so shallow copy valid
            }

            while(std::getline(recipeFile, curStrBuff) && curStrBuff.compare("notes") != 0){
                tempRecipe->appendStep(curStrBuff);
            }

            while(std::getline(recipeFile, curStrBuff) && curStrBuff.compare("-----") != 0){
                tempRecipe->appendNote(curStrBuff);
            }

            tempRecipe->calcStdCost();
            allRecipes.insert(std::pair<std::string, Recipe*>(recipeName, tempRecipe));
        }
        recipeFile.close();
    } else {
        printf("ERROR: loadRecipes failed, possibly path not valid.\n");
    }
}

/**
 * Erases current file contents and writes current data to file in given format.
 * */
void FileManager::writeIngredientsToFile(){
    std::ofstream ingredientFile;
    ingredientFile.open(ingredientPath, std::ofstream::out | std::ofstream::trunc);
    if(ingredientFile.is_open()){

        for(std::map<std::string, Ingredient*>::iterator iter = allIngredients.begin(); iter != allIngredients.end(); iter++) {
            ingredientFile << iter->first << " " << iter->second->getCost() << " " << iter->second->getAmt() << " " << iter->second->getVolUnit(); //"\n";
            if(iter->second->getMass() > 0.0) { //mass is known
                ingredientFile << " " << iter->second->getMass() << " " << iter->second->getMassUnit();
            }
            std::vector<std::string>* alts = iter->second->getAlts();
            if(alts->size() > 0) {
                for(unsigned long i = 0; i<alts->size(); i++){
                    ingredientFile << " " << alts->at(i);
                }
            }
            ingredientFile << "\n";
        }

        ingredientFile.close();
    } else {
        printf("ERROR: writeIngredientsToFile failed, possibly path not valid.\n");
    }
}

void FileManager::writeRecipesToFile(){
    std::ofstream recipeFile;
    recipeFile.open(recipePath, std::ofstream::out | std::ofstream::trunc);
    if(recipeFile.is_open()){

        for(std::map<std::string, Recipe*>::iterator iter = allRecipes.begin(); iter != allRecipes.end(); iter++) {
            recipeFile << iter->first << "\n";
            recipeFile << iter->second->getStdServings() << "\n";
            recipeFile << "ingredients\n";
            std::vector<Recipe::PortionedIngredient>* ingredients = iter->second->getIngredients();
            for (int i = 0; i<ingredients->size(); i++) {
                recipeFile << ingredients->at(i).amt.first << " " << ingredients->at(i).amt.second << " " << ingredients->at(i).ingredient << "\n";
            }
            recipeFile << "steps\n";
            std::vector<std::string>* steps = iter->second->getSteps();
            for (int i = 0; i<steps->size(); i++) {
                recipeFile << steps->at(i) << "\n";
            }
            recipeFile << "notes\n";
            std::vector<std::string>* notes = iter->second->getNotes();
            for (int i = 0; i<notes->size(); i++) {
                recipeFile << notes->at(i) << "\n";
            }
            recipeFile << "-----\n";
        }

        recipeFile.close();
    } else {
        printf("ERROR: writeRecipesToFile failed, possibly path not valid.\n");
    }
}

FileManager::~FileManager(){
    for(std::map<std::string, Ingredient*>::iterator iter = allIngredients.begin(); iter != allIngredients.end(); iter++) {
        delete iter->second;
    }

    for(std::map<std::string, Recipe*>::iterator iter = allRecipes.begin(); iter != allRecipes.end(); iter++) {
        delete iter->second;
    }
}