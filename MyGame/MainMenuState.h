#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "QuestionWindow.h"
#include "SettingsState.h"

class MainMenuState :public State
{

private:
    //переменные
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    std::map<std::string, Button*> buttons;
    sf::Font font;
    bool question; 

    //функции
    void initQuestionWindow();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();
    //функции

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);

};

#endif