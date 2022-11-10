#include "utility/textInput.h"
#include "fileManager.h"
#include "utility/button.hpp"
#include "utility/dropdownLayout.h"
#include "utility/scrollbarLayout.h"
#include <map>

class RecipeTextInput : public TextInput {
    public:
        RecipeTextInput(std::string name, sf::RenderWindow* window, int y);
        virtual void draw();
        virtual void update();
        virtual void update(sf::Event *event, int mouseX, int mouseY);

        void setScrollbarLayout(ScrollbarLayout* scrollbarLayout);
        virtual ~RecipeTextInput();
    private:
        std::string lastText;
        FileManager* fileManager;
        FileManager::RecipeHolder curSuggested;
        DropdownLayout* dropdownSuggestions;
        ScrollbarLayout* scrollWin;
        std::map<std::string, FileManager::RecipeHolder> optionsGiven; //currently a map for scalability, if more suggestions given
};