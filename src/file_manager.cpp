#include "../include/file_manager.h"

FileManager* FileManager::fileManager = nullptr;

FileManager* FileManager::newFileManager(sf::RenderWindow *window, std::string ingredientPath, std::string recipePath){
    if(fileManager == nullptr) {
        fileManager = new FileManager(window, ingredientPath, recipePath);
    }
    return fileManager;
}

FileManager* FileManager::getFileManager() {
    return fileManager;
}

FileManager::FileManager(sf::RenderWindow *window, std::string ingredientPath, std::string recipePath)
    : Element("General Manager", window){

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

    WholeIngredient* tempWholeIngredient;
    DivisibleIngredient* tempDivisibleIngredient;
    std::string ingredientName;
    std::string volUnit;
    double cost, amt;

    ingredientFile.open (ingredientPath);
    if (ingredientFile.is_open()) {

        //for each line
        while(std::getline(ingredientFile,curLine)){
            lineNum++;
            
            std::stringstream ss(curLine);
            ss >> ingredientName;
            if(allIngredients.count(ingredientName) > 0) {
                printf("WARNING duplicate ingredient name at line %d in file, second ignored.\n", lineNum);
                continue;
            }
            
            ss >> cost;
            ss >> amt;
            ss >> volUnit;

            // printf("cur vol unit is %s\n", volUnit);
            if(volUnit.compare(WHOLE_UNIT) == 0) {
                // std::cout << ingredientName << std::endl;
                tempWholeIngredient = new WholeIngredient(ingredientName, cost, amt);
            } else {
                tempDivisibleIngredient = new DivisibleIngredient(ingredientName, cost, amt, volUnit);
                if(ss >> curStrBuff) {
                    //check if double, if so then weight info known
                    std::stringstream checkDouble(curStrBuff);
                    checkDouble >> curDoubleBuff;
                    if(!checkDouble.fail()) {
                        tempDivisibleIngredient->setMass(curDoubleBuff);
                        ss >> curStrBuff;
                        tempDivisibleIngredient->setMassUnit(curStrBuff);
                    } else {
                        //read a value that's not a mass, must be alt
                        tempDivisibleIngredient->addAltIngredient(curStrBuff);
                    }
                }
                tempWholeIngredient = tempDivisibleIngredient;
            }
            
            // alt ingredients
            while (ss >> curStrBuff) {
                tempWholeIngredient->addAltIngredient(curStrBuff);
            }
            allIngredients.insert(std::pair<std::string, WholeIngredient*>(ingredientName, tempWholeIngredient));
            
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

            tempRecipe = new Recipe(recipeName);

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
                        // TODO create placeholder ingredient name, must do necessary checks to see if contains ingredient
                        printf("ERROR tried to add invalid ingredient in recipe %d under name %s\n", recipeNum, curStrBuff.c_str());
                    } else { //is a recipe type
                        tempPortionedIngredient.ingredient = (FoodComponent*) allRecipes[curStrBuff].first;
                    }
                } else { //is an ingredient type
                    tempPortionedIngredient.ingredient = (FoodComponent*) allIngredients[curStrBuff];
                }

                tempRecipe->addIngredient(tempPortionedIngredient); // not a ptr, so shallow copy valid
            }

            while(std::getline(recipeFile, curStrBuff) && curStrBuff.compare("notes") != 0){
                tempRecipe->appendStep(curStrBuff);
            }

            while(std::getline(recipeFile, curStrBuff) && curStrBuff.compare("-----") != 0){
                tempRecipe->appendNote(curStrBuff);
            }

            tempRecipe->calcStdCost();

            //init nullptr recipedisplays
            allRecipes.insert(std::pair<std::string, std::pair<Recipe*, RecipeDisplay*>>(recipeName, std::pair<Recipe*, RecipeDisplay*>(tempRecipe, nullptr)));

            // printf("writing a recipe!\n");
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

        for(std::map<std::string, WholeIngredient*>::iterator iter = allIngredients.begin(); iter != allIngredients.end(); iter++) {
            ingredientFile << iter->first << " " << iter->second->getCost() << " " << iter->second->getAmt();// << " " << iter->second->getVolUnit(); //"\n";
    
            //if it is a divisible ingredient
            if (dynamic_cast<DivisibleIngredient*>(iter->second)) {
                DivisibleIngredient* tempCast = (DivisibleIngredient*) iter->second;
                ingredientFile << " " << tempCast->getVolUnit();
                if(tempCast->getMass() > 0.0) { //mass is known
                    ingredientFile << " " << tempCast->getMass() << " " << tempCast->getMassUnit();
                }
            } else { //whole ingredient
                ingredientFile << " " << WHOLE_UNIT;
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

        for(std::map<std::string, std::pair<Recipe*, RecipeDisplay*>>::iterator iter = allRecipes.begin(); iter != allRecipes.end(); iter++) {
            recipeFile << iter->first << "\n";
            recipeFile << iter->second.first->getStdServings() << "\n";
            recipeFile << "ingredients\n";
            const std::vector<Recipe::PortionedIngredient>* ingredients = iter->second.first->getIngredients();
            for (unsigned long i = 0; i<ingredients->size(); i++) {
                recipeFile << ingredients->at(i).amt.first << " " << ingredients->at(i).amt.second << " " << ingredients->at(i).ingredient->getName() << "\n";
            }
            recipeFile << "steps\n";
            const std::vector<std::string>* steps = iter->second.first->getSteps();
            for (unsigned long i = 0; i<steps->size(); i++) {
                recipeFile << steps->at(i) << "\n";
            }
            recipeFile << "notes\n";
            const std::vector<std::string>* notes = iter->second.first->getNotes();
            for (unsigned long i = 0; i<notes->size(); i++) {
                recipeFile << notes->at(i) << "\n";
            }
            recipeFile << "-----\n";
        }

        recipeFile.close();
    } else {
        printf("ERROR: writeRecipesToFile failed, possibly path not valid.\n");
    }
}

void FileManager::displayRecipesInit(int centerX, int startY) {
    // printf("%s", allRecipes);
    for(std::map<std::string, std::pair<Recipe*, RecipeDisplay*>>::iterator iter = allRecipes.begin(); iter != allRecipes.end(); iter++) {
        //init recipeDisplays
        if(iter->second.second == nullptr && iter->second.first != nullptr) {
            //todo get rid of magic number
            printf("creating a recipedisplay! y start being %d\n", startY);
            iter->second.second = new RecipeDisplay(window, iter->second.first, centerX - 200, startY, 400);
            startY += RecipeDisplay::TITLE_HEIGHT * 2; //2x spacing
        }    
    }
}

void FileManager::draw() {
    for(std::map<std::string, std::pair<Recipe*, RecipeDisplay*>>::iterator iter = allRecipes.begin(); iter != allRecipes.end(); iter++) {
        //recipeDisplay exists
        if(iter->second.second != nullptr) {
            iter->second.second->draw(); //2x spacing
        }
    }
}

void FileManager::update(sf::Event* event, int mouseX, int mouseY) {
    int curOffset = 0;
    for(std::map<std::string, std::pair<Recipe*, RecipeDisplay*>>::iterator iter = allRecipes.begin(); iter != allRecipes.end(); iter++) {
        //recipeDisplay exists
        if(iter->second.second != nullptr) {
            iter->second.second->shiftYVal(curOffset);
            iter->second.second->update(event, mouseX, mouseY); //2x spacing
            // if(iter->second.second->getChanged() == RecipeDisplay::expanded) {
            curOffset += iter->second.second->getExtraHeight();
            // } else if(iter->second.second->getChanged() == RecipeDisplay::minimized){
                // curOffset -= iter->second.second->getExtraHeight();
            // }
        }    
    }
}

FileManager::~FileManager(){
    for(std::map<std::string, WholeIngredient*>::iterator iter = allIngredients.begin(); iter != allIngredients.end(); iter++) {
        delete iter->second;
    }

    for(std::map<std::string, std::pair<Recipe*, RecipeDisplay*>>::iterator iter = allRecipes.begin(); iter != allRecipes.end(); iter++) {
        delete iter->second.first;
        delete iter->second.second;
    }
}