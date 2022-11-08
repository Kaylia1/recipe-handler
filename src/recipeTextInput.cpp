#include "../include/recipeTextInput.h"

//todo

RecipeTextInput::RecipeTextInput(std::string name, sf::RenderWindow* window, int y) : TextInput(name, window, y) {
    fileManager = FileManager::getFileManager();
    lastText = "";
    // printf("xmin %d xmax %d\n", xMin, xMax);
    dropdownSuggestions = new DropdownLayout("suggestions", window, xMin, yMax, xMax); //yMax of input is yMin of dropdown
}

void RecipeTextInput::draw() {
    TextInput::draw();

    if(index >= 0 && lastText.size() > 0) { //selected, show suggestions
        // printf("trying to draw dropdown");
        dropdownSuggestions->draw();
    }
}

void RecipeTextInput::update() {
    // dropdownSuggestions->update(); //none currently
    // printf("in update\n");

    if(index >= 0 && enteredText.size() > 0 && enteredText.compare(lastText) != 0) { //selected and something new entered
        lastText = enteredText;
        curSuggested = fileManager->getMostSimilarName(enteredText);
        dropdownSuggestions->clear();

        // printf("is name valid? %s\n", curSuggested.recipe->getName().c_str());
        dropdownSuggestions->addOption(curSuggested.recipe->getName());
    }
}


void RecipeTextInput::update(sf::Event *event, int mouseX, int mouseY) {
    // printf("in event update\n");
    TextInput::update(event, mouseX, mouseY);

    if(index >= 0 && lastText.size() > 0) { //selected, show suggestions
        dropdownSuggestions->update(event, mouseX, mouseY);
    }
}

RecipeTextInput::~RecipeTextInput(){
    delete dropdownSuggestions;
}