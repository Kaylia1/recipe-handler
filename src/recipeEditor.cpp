#include "../include/recipeEditor.h"

const int RecipeEditor::LINE_HEIGHT = 30;
const int RecipeEditor::SPACING_HEIGHT = 10;
const int RecipeEditor::MIN_X_INIT = -100;
const int RecipeEditor::MAX_X_INIT = 100;

RecipeEditor::RecipeEditor(sf::RenderWindow *window, int windowWidth, int windowHeight) : Element("new recipe", window),
    enterName("name", window, 100),

    recipeScrollbar("recipe scrollbar", window, windowWidth, windowHeight, 100, 200, windowWidth - 200, 400, 10000) {

    ingredientY = 240;
    instructionY = 280;
    noteY = 320;

    addIngredient = std::make_shared<Button<RecipeEditor>>(this, &RecipeEditor::newIngredient, "add ingredient", window,
        MIN_X_INIT, (int)recipeScrollbar.translateInnerElementY(50),
        MAX_X_INIT, (int)recipeScrollbar.translateInnerElementY(50 + LINE_HEIGHT));
    addInstruction = std::make_shared<Button<RecipeEditor>>(this, &RecipeEditor::newInstruction, "add instruction", window,
        MIN_X_INIT, (int)recipeScrollbar.translateInnerElementY(90),
        MAX_X_INIT, (int)recipeScrollbar.translateInnerElementY(90 + LINE_HEIGHT));
    addNote = std::make_shared<Button<RecipeEditor>>(this, &RecipeEditor::newNote, "add note", window,
        MIN_X_INIT, (int)recipeScrollbar.translateInnerElementY(130),
        MAX_X_INIT, (int)recipeScrollbar.translateInnerElementY(130 + LINE_HEIGHT));

    recipeScrollbar.addInnerElement(addIngredient, false);
    recipeScrollbar.addInnerElement(addInstruction, false);
    recipeScrollbar.addInnerElement(addNote), false);

    //todo add scrollbar

}

void RecipeEditor::update() {
    recipeScrollbar.update();
}

void RecipeEditor::update(sf::Event *event, int mouseX, int mouseY) {
    enterName.update(event, mouseX, mouseY);

    recipeScrollbar.update(event, mouseX, mouseY);

    // addIngredient.update(event, mouseX, mouseY);
    // addInstruction.update(event, mouseX, mouseY);
    // addNote.update(event, mouseX, mouseY);

    for(unsigned long i = 0; i < enterIngredients.size(); i++) {
        enterIngredients[i]->update(event, mouseX, mouseY);
    }
    for(unsigned long i = 0; i < enterInstructions.size(); i++) {
        enterInstructions[i]->update(event, mouseX, mouseY);
    }
    for(unsigned long i = 0; i < enterNotes.size(); i++) {
        enterNotes[i]->update(event, mouseX, mouseY);
    }
}

void RecipeEditor::draw() {
    enterName.draw();
    // addIngredient.draw();
    // addInstruction.draw();
    // addNote.draw();

    recipeScrollbar.draw();

    for(unsigned long i = 0; i < enterIngredients.size(); i++) {
        enterIngredients[i]->draw();
    }
    for(unsigned long i = 0; i < enterInstructions.size(); i++) {
        enterInstructions[i]->draw();
    }
    for(unsigned long i = 0; i < enterNotes.size(); i++) {
        enterNotes[i]->draw();
    }
}

std::unique_ptr<Recipe> RecipeEditor::saveRecipe() {
    if(enterName.getEnteredText().size() == 0) {
        return nullptr;
    }
    std::unique_ptr<Recipe> curRecipe = std::make_unique<Recipe>(enterName.getEnteredText());

    //TODO fix
    // for(unsigned long i = 0; i < enterIngredients.size(); i++) {
        // curRecipe->addIngredient(enterIngredients[i].getEnteredText()); //todo figure out if recipe or ingredient is being added
    // }
    for(unsigned long i = 0; i < enterInstructions.size(); i++) {
        curRecipe->appendStep(enterInstructions[i]->getEnteredText()); //todo figure out if recipe or ingredient is being added
    }
    for(unsigned long i = 0; i < enterIngredients.size(); i++) {
        curRecipe->appendNote(enterNotes[i]->getEnteredText()); //todo figure out if recipe or ingredient is being added
    }

    return curRecipe;

}

//todo fix ingredient save
void RecipeEditor::newIngredient(Button<RecipeEditor> *id) {
    // printf("size is %d\n", enterIngredients.size());

    enterIngredients.push_back(std::make_unique<TextInput>("ingredient" + enterIngredients.size(), window, ingredientY));
    ingredientY += LINE_HEIGHT + SPACING_HEIGHT;
    instructionY += LINE_HEIGHT + SPACING_HEIGHT;
    noteY += LINE_HEIGHT + SPACING_HEIGHT;

    addInstruction.changeSize(MIN_X_INIT, ingredientY, MAX_X_INIT, ingredientY + LINE_HEIGHT);
    addNote.changeSize(MIN_X_INIT, instructionY, MAX_X_INIT, instructionY + LINE_HEIGHT);
    for(unsigned long i = 0; i < enterInstructions.size(); i++) {
        enterInstructions[i]->shiftDown(LINE_HEIGHT + SPACING_HEIGHT);
    }
    for(unsigned long i = 0; i < enterNotes.size(); i++) {
        enterNotes[i]->shiftDown(LINE_HEIGHT + SPACING_HEIGHT);
    }
}
void RecipeEditor::newInstruction(Button<RecipeEditor> *id) {
    enterInstructions.push_back(std::make_unique<TextInput>("instruction" + enterInstructions.size(), window, instructionY));
    instructionY += LINE_HEIGHT + SPACING_HEIGHT;
    noteY += LINE_HEIGHT + SPACING_HEIGHT;

    addNote.changeSize(MIN_X_INIT, instructionY, MAX_X_INIT, instructionY + LINE_HEIGHT);
    for(unsigned long i = 0; i < enterNotes.size(); i++) {
        enterNotes[i]->shiftDown(LINE_HEIGHT + SPACING_HEIGHT);
    }
}
void RecipeEditor::newNote(Button<RecipeEditor> *id) {
    enterNotes.push_back(std::make_unique<TextInput>("note" + enterNotes.size(), window, noteY));
    noteY += LINE_HEIGHT + SPACING_HEIGHT; //todo what is textinput height
}

//todo add load option so it is editor not just create new

RecipeEditor::~RecipeEditor() {
    //unique_ptr handles destructors
}