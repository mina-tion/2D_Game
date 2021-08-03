#ifndef STATE_H
#define STATE_H

#include "QuestionWindow.h"
#include "Player.h"
#include "GraphicsSettings.h"

class Player;
class QuestionWindow;
class State;

class StateData
{
public: 
	StateData()
	{
		this->window = NULL;
		this->states = NULL;
		this->gSettings = NULL;
		this->supportedKeys = NULL;
	};

	sf::RenderWindow* window;
	GraphicSettings* gSettings;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;

};

class State
{
private:

protected:
	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	sf::View view;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;

	QuestionWindow* questionWindow;


	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//ресурсы
	std::map<std::string, sf::Texture> textures;

	//функции
	virtual void initKeybinds() = 0;

public:

	State(StateData* state_data);
	virtual ~State();

	const bool& getQuit() const;
	const bool getKeytime();

	//virtual void checkForQuit();
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions();
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float &dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget *target = NULL) = 0;
};
#endif

