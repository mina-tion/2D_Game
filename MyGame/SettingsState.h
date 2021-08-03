#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H
#include "GameState.h"
#include "Button.h"

class SettingsState :
    public State
{
private: 
    //переменные
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    std::map<std::string, Button*> buttons;
    sf::Font font;
    sf::Text fullscreenText;

    //функции
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
    void initText();
public:
    SettingsState(StateData* state_data);
    virtual ~SettingsState();

    //функции
    void updateGui(const float& dt);
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);

};

#endif