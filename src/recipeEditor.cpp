#include "../include/recipeEditor.h"

const int RecipeEditor::LINE_HEIGHT = 30;
const int RecipeEditor::SPACING_HEIGHT = 10;
const int RecipeEditor::MIN_X_INIT = -100;
const int RecipeEditor::MAX_X_INIT = 100;
const int RecipeEditor::MIN_X_INPUT = -200;
const int RecipeEditor::MAX_X_INPUT = 200;

RecipeEditor::RecipeEditor(sf::RenderWindow *window, int windowWidth, int windowHeight) : Element("new recipe", window),
    enterName("name", window, 100),

    recipeScrollbar("recipe scrollbar", window, windowWidth, windowHeight, 75, 200, windowWidth - 175, 300, 5000) {

    ingredientY = (int)recipeScrollbar.translateInnerElementY(10);
    instructionY = (int)recipeScrollbar.translateInnerElementY(50);
    noteY = (int)recipeScrollbar.translateInnerElementY(90);

    addIngredient = std::make_shared<Button<RecipeEditor>>(this, &RecipeEditor::newIngredient, "add ingredient", window,
        MIN_X_INIT, ingredientY,
        MAX_X_INIT, ingredientY + LINE_HEIGHT);
    addInstruction = std::make_shared<Button<RecipeEditor>>(this, &RecipeEditor::newInstruction, "add instruction", window,
        MIN_X_INIT, instructionY,
        MAX_X_INIT, instructionY + LINE_HEIGHT);
    addNote = std::make_shared<Button<RecipeEditor>>(this, &RecipeEditor::newNote, "add note", window,
        MIN_X_INIT, noteY,
        MAX_X_INIT, noteY + LINE_HEIGHT);
    ingredientY += LINE_HEIGHT + SPACING_HEIGHT;
    instructionY += LINE_HEIGHT + SPACING_HEIGHT;
    noteY += LINE_HEIGHT + SPACING_HEIGHT;

    recipeScrollbar.addInnerElement(addIngredient);
    recipeScrollbar.addInnerElement(addInstruction);
    recipeScrollbar.addInnerElement(addNote);

    //todo add servings

}

void RecipeEditor::update() {
    recipeScrollbar.update();
}

void RecipeEditor::update(sf::Event *event, int mouseX, int mouseY) {
    enterName.update(event, mouseX, mouseY);

    recipeScrollbar.update(event, mouseX, mouseY);
}

void RecipeEditor::draw() {
    enterName.draw();

    recipeScrollbar.draw();
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

    return std::move(curRecipe);

}

//todo fix ingredient save
void RecipeEditor::newIngredient(Button<RecipeEditor> *id) {
    // todo split by name (search), amount
    std::shared_ptr<TextInput> ingredient = std::make_shared<TextInput>("ingredient" + enterIngredients.size(), window, MIN_X_INPUT, ingredientY, MAX_X_INPUT, ingredientY + 25); // magic number
    enterIngredients.push_back(ingredient);
    recipeScrollbar.addInnerElement(ingredient);

    ingredientY += LINE_HEIGHT + SPACING_HEIGHT;
    instructionY += LINE_HEIGHT + SPACING_HEIGHT;
    noteY += LINE_HEIGHT + SPACING_HEIGHT;

    addInstruction->changeSize(MIN_X_INIT, ingredientY, MAX_X_INIT, ingredientY + LINE_HEIGHT);
    addNote->changeSize(MIN_X_INIT, instructionY, MAX_X_INIT, instructionY + LINE_HEIGHT);
    for(unsigned long i = 0; i < enterInstructions.size(); i++) {
        enterInstructions[i]->shiftDown(LINE_HEIGHT + SPACING_HEIGHT);
    }
    for(unsigned long i = 0; i < enterNotes.size(); i++) {
        enterNotes[i]->shiftDown(LINE_HEIGHT + SPACING_HEIGHT);
    }
}
void RecipeEditor::newInstruction(Button<RecipeEditor> *id) {

    std::shared_ptr<TextInput> instruction = std::make_shared<TextInput>("instruction" + enterInstructions.size(), window, MIN_X_INPUT, instructionY, MAX_X_INPUT, instructionY + 25);
    enterInstructions.push_back(instruction);
    recipeScrollbar.addInnerElement(instruction);

    instructionY += LINE_HEIGHT + SPACING_HEIGHT;
    noteY += LINE_HEIGHT + SPACING_HEIGHT;

    addNote->changeSize(MIN_X_INIT, instructionY, MAX_X_INIT, instructionY + LINE_HEIGHT);
    for(unsigned long i = 0; i < enterNotes.size(); i++) {
        enterNotes[i]->shiftDown(LINE_HEIGHT + SPACING_HEIGHT);
    }
}
void RecipeEditor::newNote(Button<RecipeEditor> *id) {
    std::shared_ptr<TextInput> note = std::make_shared<TextInput>("note" + enterNotes.size(), window, MIN_X_INPUT, noteY, MAX_X_INPUT, noteY + 25);
    enterNotes.push_back(note);
    recipeScrollbar.addInnerElement(note);
    noteY += LINE_HEIGHT + SPACING_HEIGHT; //todo what is textinput height
}

//todo add load option so it is editor not just create new

RecipeEditor::~RecipeEditor() {}