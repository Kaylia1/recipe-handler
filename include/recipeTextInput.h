#include "utility/textInput.h"
#include "fileManager.h"
#include "utility/button.hpp"
#include "utility/dropdownLayout.h"

class RecipeTextInput : public TextInput {
    public:
        RecipeTextInput(std::string name, sf::RenderWindow* window, int y);
        virtual void draw();
        virtual void update();
        virtual void update(sf::Event *event, int mouseX, int mouseY);
        virtual ~RecipeTextInput();
    private:
        std::string lastText;
        FileManager* fileManager;
        FileManager::RecipeHolder curSuggested;
        DropdownLayout* dropdownSuggestions;
};