#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "Map.h"
#include "Npc.h"
#include "Teleport.h" 
#include "Mission.h"


class GameState: public State
{
private:
    sf::Font font;
    PauseMenu* pmenu;
    sf::View view;
    
    Player* player;
    Npc* npcWoman;
    Npc* npcMan;
    Teleport* teleportOnFirst;
    Teleport* teleportOnSecond;
    Mission* startMission;


    sf::Sprite coinSprite;
    sf::Sprite signSprite;
    sf::Sprite missionFormSprite;

    std::map<std::string, Map*> locations;
    std::string currentLocation;
    std::string saveFile;

    sf::Text coinsText;
    sf::Text interactionText;
    sf::Text missionText;

    bool questionQuit;
    bool questionSave;

    //функции
    void initQuestionWindow();
    void initKeybinds();
    void initTextures();
    void initPlayers();
    void initNpc();
    void initObjects();
    void initLocations();
    void initFonts();
    void initTextObjects();
    void initPauseMenu();
    void initMissions();

    void loadSaves();

public: 
    GameState(StateData* state_data);
    GameState(StateData* state_data, std::string save_file);
    virtual ~GameState();

  
    //функции
    void updateInput(const float&dt);
    void updateView(std::string map);
    void updateMap();
    void updateObjects(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void updateTextObjects();
    void render(sf::RenderTarget* target = NULL);
    
};

#endif

