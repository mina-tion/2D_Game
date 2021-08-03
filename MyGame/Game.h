#ifndef GAME_H
#define GAME_H
#include "MainMenuState.h"

class Game
{
private:
	//переменные
	GraphicSettings gSettings;
	sf::RenderWindow* window;
	sf::Event sfEvent;

	StateData stateData;
	std::stack<State*> states;
	
	
	sf::Clock dtClock;
	float dt;


	std::map<std::string, int> supportedKeys;

	//регулярные
	void endApplication();

	//обновление
	void updateDt();
	void update();
	void updateSfEvents();

	//отрисовка
	void render();

	//инициализация
	void initVariables();
	void initGraphicSettings();
	void initStateData();
	void initWindow();
	void initKeys();
	void initStates();


public:

	Game();
	virtual ~Game();

	//запуск игры
	void run();

};

#endif