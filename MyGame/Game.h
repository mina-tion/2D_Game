#ifndef GAME_H
#define GAME_H
#include "MainMenuState.h"

class Game
{
private:
	//����������
	GraphicSettings gSettings;
	sf::RenderWindow* window;
	sf::Event sfEvent;

	StateData stateData;
	std::stack<State*> states;
	
	
	sf::Clock dtClock;
	float dt;


	std::map<std::string, int> supportedKeys;

	//����������
	void endApplication();

	//����������
	void updateDt();
	void update();
	void updateSfEvents();

	//���������
	void render();

	//�������������
	void initVariables();
	void initGraphicSettings();
	void initStateData();
	void initWindow();
	void initKeys();
	void initStates();


public:

	Game();
	virtual ~Game();

	//������ ����
	void run();

};

#endif