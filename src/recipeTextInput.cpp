#include "../include/recipeTextInput.h"

//todo

RecipeTextInput::RecipeTextInput(std::string name, sf::RenderWindow* window, int y) : TextInput(name, window, y) {
    fileManager = FileManager::getFileManager();
    lastText = "";
    scrollWin = nullptr;
    dropdownSuggestions = new DropdownLayout("suggestions", window, xMin, yMax, xMax); //yMax of input is yMin of dropdown
}

void RecipeTextInput::setScrollbarLayout(ScrollbarLayout* scrollbarLayout) {
    scrollWin = scrollbarLayout;
}

void RecipeTextInput::draw() {
    TextInput::draw();

    if(index >= 0 && lastText.size() > 0) { //selected, show suggestions
        dropdownSuggestions->draw();
    }
}

void RecipeTextInput::update() {
    // dropdownSuggestions->update(); //none currently

    if(index >= 0 && enteredText.size() > 0 && enteredText.compare(lastText) != 0) { //selected and something new entered
        optionsGiven.clear();

        lastText = enteredText;
        curSuggested = fileManager->getMostSimilarName(enteredText);
        dropdownSuggestions->clear();
        dropdownSuggestions->addOption(curSuggested.recipe->getName());

        optionsGiven[curSuggested.recipe->getName()] = curSuggested;
    }

    std::string curOpt = dropdownSuggestions->getCurOption(); //getcuropt broken
    if(curOpt.size() > 0 && scrollWin != nullptr && dropdownSuggestions->getSelected()) { //none empty

        // why is minus making show y increase
        scrollWin->moveToWindowY( (int) scrollWin->decodeInnerElementY(optionsGiven[curOpt].display->getMinY()) - 10); //magic number
    }
}


void RecipeTextInput::update(sf::Event *event, int mouseX, int mouseY) {

    dropdownSuggestions->update(event, mouseX, mouseY); //need to update to update isSelected

    TextInput::update(event, mouseX, mouseY);
}

RecipeTextInput::~RecipeTextInput(){
    delete dropdownSuggestions;
}