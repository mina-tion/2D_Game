#include "stdafx.h"
#include "GameState.h"
GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initLocations();
	this->initPlayers();
	this->initNpc();
	this->initObjects();
	this->initPauseMenu();
	this->initMissions();
	this->initQuestionWindow();
	//камера вида
	this->view.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	this->view.setCenter(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
	this->currentLocation = "START_LOCATION";
	this->initTextObjects();
	this->questionSave = false;
	this->questionQuit = false;
}

GameState::GameState(StateData* state_data, std::string save_file)
	:State(state_data)
{
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initLocations();
	this->initPlayers();
	this->initNpc();
	this->initObjects();
	this->initTextObjects();
	this->initPauseMenu();
	this->initMissions();
	this->initTextObjects();
	this->initQuestionWindow();

	//камера вида
	this->view.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	this->saveFile = save_file;
	this->loadSaves();
	this->questionSave = false;
	this->questionQuit = false;
}


void GameState::loadSaves()
{
	float x = 0.f;
	float y = 0.f;
	int coins = 0; 
	bool active = 0;
	bool complete = 0;
	int step = 0;
	std::string tempText = "";

	std::ifstream ifs(this->saveFile);
	if (ifs.is_open())
	{
		ifs >> x >> y;
		ifs >> this->currentLocation;
		ifs >> coins;
		ifs >> active;
		ifs >> step;
		ifs >> complete;
		while (std::getline(ifs, tempText)) 
		{ 
			this->interactionText.setString(tempText);
			this->missionText.setString(tempText);
		}

	}
	ifs.close();
	this->player->setPosition(x, y);
	this->player->setCoins(coins);
	
	if (active == 1)
		this->startMission->activateMission();
	if (step != 0)
		this->startMission->setStep(step);
	if (complete == 1)
		this->startMission->comleteMission();
}

GameState::~GameState()
{
	delete this->player;
	delete this->npcMan;
	delete this->npcWoman;
	delete this->teleportOnFirst;
	delete this->teleportOnSecond;
	delete this->startMission;
	delete this->questionWindow;


	delete this->pmenu;
	auto it = this->locations.begin();
	for (it = this->locations.begin(); it != this->locations.end(); ++it)
	{
		delete it->second;
	}
}


//#################################     »Ќ»÷»јЋ»«ј÷»я      #################################

void GameState::initQuestionWindow()
{
	this->questionWindow = new QuestionWindow(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y),
		&this->font, "Are you sure you want to quit?");
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}


void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resourses/Images/Sprites/player.png"))
	{
		throw "ERROR::GAME_STATE::PLAYER_TEXTURE";
	}
	if (!this->textures["NPC_WOMAN_SHEET"].loadFromFile("Resourses/Images/Sprites/woman.png"))
	{
		throw "ERROR::GAME_STATE::NPC_TEXTURE";
	}
	if (!this->textures["NPC_MAN_SHEET"].loadFromFile("Resourses/Images/Sprites/man.png"))
	{
		throw "ERROR::GAME_STATE::NPC_TEXTURE";
	}
	if (!this->textures["TELEPORT_SHEET"].loadFromFile("Resourses/Images/Sprites/teleport_2.png"))
	{
		throw "ERROR::GAME_STATE::TELEPORT_TEXTURE";
	}
	if (!this->textures["COIN"].loadFromFile("Resourses/Images/coin.png"))
	{
		throw "ERROR::GAME_STATE::COIN_TEXTURE";
	}
	if (!this->textures["SIGN"].loadFromFile("Resourses/Images/exclamation.png"))
	{
		throw "ERROR::GAME_STATE::COIN_TEXTURE";
	}
	if (!this->textures["MISSIONFORM"].loadFromFile("Resourses/Images/missionForm.png"))
	{
		throw "ERROR::GAME_STATE::MISSION_TEXTURE";
	}

}

void GameState::initPlayers()
{
	this->player = new Player(300, 300, this->textures["PLAYER_SHEET"]);
}

void GameState::initNpc()
{
	this->npcWoman = new Npc(500, 700, this->textures["NPC_WOMAN_SHEET"]);
	this->npcMan = new Npc(990, 1000, this->textures["NPC_MAN_SHEET"]);
}

void GameState::initObjects()
{
	this->teleportOnFirst = new Teleport(500, 200, this->textures["TELEPORT_SHEET"]);
	this->teleportOnSecond = new Teleport(1200, 1500, this->textures["TELEPORT_SHEET"]);

	this->coinSprite.setTexture(this->textures["COIN"]);
	this->signSprite.setTexture(this->textures["SIGN"]);

	this->missionFormSprite.setTexture(this->textures["MISSIONFORM"]);
	
}

void GameState::initLocations()
{
	this->locations["START_LOCATION"] = new Map(100, 100, "Resourses/map.txt");
	this->locations["SECOND_LOCATION"] = new Map(100, 100, "Resourses/map2.txt");
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("fonts/GOTHIC.TTF"))
	{
		throw("ERROR::MAIMMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initTextObjects()
{
	this->coinsText.setFont(this->font);
	this->coinsText.setFillColor(sf::Color(235, 194, 167));
	this->coinsText.setCharacterSize(30);
	this->coinsText.setStyle(sf::Text::Bold);
	this->coinsText.setString("");

	this->interactionText.setFont(this->font);
	this->interactionText.setFillColor(sf::Color(235, 194, 167));
	this->interactionText.setCharacterSize(20);
	this->interactionText.setStyle(sf::Text::Bold);
	this->interactionText.setString("");

	this->missionText.setFont(this->font);
	this->missionText.setFillColor(sf::Color(235, 194, 167));
	this->missionText.setCharacterSize(20);
	this->missionText.setStyle(sf::Text::Bold);
	this->missionText.setString("");

}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->addButton("SAVE", 400.f, "Save game");
	this->pmenu->addButton("QUIT", 600.f, "Quit");

}

void GameState::initMissions()
{
	this->startMission = new Mission();
}


//#################################     ќЅЌќ¬Ћ≈Ќ»≈      #################################

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!paused)
			this->pauseState();
		else
			this->unpauseState();
	}

}

void GameState::updateView(std::string map)
{
	float tempX = this->player->getPosition().x; 
	float tempY = this->player->getPosition().y;
	float endX = this->locations[map]->getSize().x;
	float endY = this->locations[map]->getSize().y;
	//убираем левую сторону
	if (this->player->getPosition().x < this->window->getSize().x / 2.f)
		tempX = this->window->getSize().x / 2.f;

	//убираем правую сторону
	if (this->player->getPosition().x > endX - (this->window->getSize().x / 2.f))
		tempX = endX - (this->window->getSize().x / 2.f);

	//убираем верхнюю сторону
	if (this->player->getPosition().y  < this->window->getSize().y / 2.f)
		tempY = this->window->getSize().y / 2.f;

	//убираем нижнюю сторону
	if (this->player->getPosition().y  > endY - (this->window->getSize().y / 2.f))
		tempY = endY - (this->window->getSize().y / 2.f);

	this->view.setCenter(tempX, tempY);
}

void GameState::updateMap()
{
	this->locations[this->currentLocation]->updateCollision(this->player);
}

void GameState::updateObjects(const float& dt)
{

	//_________________ѕ≈–¬јя Ћќ ј÷»я______________________________________
	this->coinSprite.setPosition(this->view.getCenter().x + this->window->getSize().x / 2.f - 100,
		this->view.getCenter().y - this->window->getSize().y / 2.f + 25);

	if (this->currentLocation == "START_LOCATION")
	{
		//взаимодействие персонажа с телепортом
		if (this->teleportOnFirst->getInteraction(this->player))
		{
			this->teleportOnFirst->updateAnimation(dt);
			
			this->interactionText.setString("Press ENTER to change location");
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INTERACTIVE"))))
			{
				this->player->setPosition(
					this->teleportOnSecond->getPosition().x + 90,
					this->teleportOnSecond->getPosition().y + 30);
				this->currentLocation = "SECOND_LOCATION";
			}
		}
		else 
			this->teleportOnFirst->update(dt);

		this->npcWoman->update(dt);
		
		//взаимодействие персонажа с Ќѕ—
		if (this->npcWoman->getInteraction(this->player))
		{
			if (!this->startMission->isActive() && !this->startMission->isComplited())
			{
				this->interactionText.setString("Press ENTER to active mission");
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INTERACTIVE"))))
				{
					this->missionText.setString("Find the hairpin.That woman lost it in the flower field");
					if (this->startMission->getStep() == 0)
						this->startMission->activateMission();
				}
			}
			else if (this->startMission->isActive() && !this->startMission->isComplited())
			{
				if (this->startMission->getStep() < 3)
				{
					this->interactionText.setString("Press BACKSPACE to deactive mission");
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DEACTIVE"))))
					{
						this->startMission->deactivateMission();
					}
				}

				else if (this->startMission->getStep() == 3)
				{
					this->interactionText.setString("Press ENTER to complete mission");
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INTERACTIVE"))))
					{
						this->startMission->comleteMission();
						this->startMission->deactivateMission();
						this->player->changeCoins(50);
						this->interactionText.setString("");
						this->missionText.setString("");
					}
				}
			}
		}
		this->signSprite.setPosition(this->npcWoman->getPosition().x - 5,
			this->npcWoman->getPosition().y - 50);
	}

//_________________¬“ќ–јя Ћќ ј÷»я______________________________________
	else if (this->currentLocation == "SECOND_LOCATION")
	{
		//взаимодействие персонажа с телепортом
		if (this->teleportOnSecond->getInteraction(this->player))
		{
			this->teleportOnSecond->updateAnimation(dt);
			this->interactionText.setString("Press ENTER to change location");

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INTERACTIVE"))))
			{
				this->player->setPosition(
					this->teleportOnFirst->getPosition().x + 90,
					this->teleportOnFirst->getPosition().y + 30);
				this->currentLocation = "START_LOCATION";
			}
		}
		else
			this->teleportOnSecond->update(dt);
		this->npcMan->update(dt);

		//взаимодействие персонажа с Ќѕ—
		if (this->npcMan->getInteraction(this->player))
		{
			if (this->startMission->isActive())
			{
				if (this->startMission->getStep() == 1)//получение подсказки
				{
					this->interactionText.setString("Press ENTER for a prompt");

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INTERACTIVE"))))
					{
						this->missionText.setString("This man is ready to exchange the hairpin for 30 coins.");
						this->startMission->setStep(2);
					}
				}
				
				if (this->startMission->getStep() == 2)//происходит обмен
				{
					this->interactionText.setString("Press BACKSPACE to exchange");

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DEACTIVE"))))
					{
						this->missionText.setString("The exchange was successful. Return the hairpin to the woman.");
						this->startMission->setStep(3);
						this->player->changeCoins(-30);
						this->interactionText.setString("");
					}
				}
			}
			else this->interactionText.setString("");
		}
		this->signSprite.setPosition(this->npcMan->getPosition().x - 5,
			this->npcMan->getPosition().y - 50);
	}		

	this->missionFormSprite.setPosition(this->view.getCenter().x - this->window->getSize().x / 2.f + 35,
		this->view.getCenter().y - this->window->getSize().y / 2.f + 25);
}


void GameState::updatePlayerInput(const float& dt)
{
	//обработка нажатий клавиш игроком
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);		

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);

}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->questionWindow->changeText("Are you sure you want to quit?");
		this->questionQuit = true;
	}

	if (this->questionQuit)
	{
		//обновление окна и кнопок
		this->questionWindow->update(this->mousePosView);

		if (this->questionWindow->checkPressedKey() == 2)
			this->questionQuit = false;
		if (this->questionWindow->checkPressedKey() == 1)
		{
			this->questionQuit = false;
			this->endState();
		}
	}

	if (this->pmenu->isButtonPressed("SAVE"))
	{
		this->questionWindow->changeText("Are you sure you want to rewrite saves?");
		this->questionSave = true;
	}

	std::string interactionT = this->interactionText.getString();
	std::string missionT = this->missionText.getString();


	if (this->questionSave)
	{
		//обновление окна и кнопок
		this->questionWindow->update(this->mousePosView);

		if (this->questionWindow->checkPressedKey() == 2)
			this->questionSave = false;
		if (this->questionWindow->checkPressedKey() == 1)
		{
			std::ofstream ofs("Config/saves.ini");
			if (ofs.is_open())
			{
				ofs << this->player->getPosition().x << " " << this->player->getPosition().y << "\n"; //коррдинаты игрока
				ofs << this->currentLocation << "\n"; //название локации
				ofs << this->player->getCoins() << "\n"; //монеты
				ofs << this->startMission->isActive() << "\n"; //активна ли мисси€
				ofs << this->startMission->getStep() << "\n"; //шаг выполнени€ миссии
				ofs << this->startMission->isComplited() << "\n"; //выполнена ли мисси€
				ofs << interactionT << "\n";//текст взаимодействи€
				ofs << missionT << "\n";//текст миссии
			}
			ofs.close();
			this->questionSave = false;
		}
	}
}

void GameState::updateTextObjects()
{
	std::ostringstream scoreString;
	scoreString << this->player->getCoins();
	this->coinsText.setString(scoreString.str());

	this->coinsText.setPosition(
		this->view.getCenter().x + this->window->getSize().x / 2.f - 150, 
		this->view.getCenter().y - this->window->getSize().y / 2.f + 35);

	this->interactionText.setPosition(
		this->view.getCenter().x - this->window->getSize().x / 4.f + this->interactionText.getGlobalBounds().width / 2.f,
		this->view.getCenter().y + this->window->getSize().y / 3.f);

	this->missionText.setPosition(
		this->view.getCenter().x - this->window->getSize().x / 2.f + 75,
		this->view.getCenter().y - this->window->getSize().y / 2.f + 100);
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);
	if (!this->paused)//обновление, пока не на паузе
	{
		this->updatePlayerInput(dt);
		this->updateView(this->currentLocation);
		this->player->update(dt);
		this->updateMap();
		this->updateObjects(dt);
	}
	else //обновление, пока на паузе
	{
		this->view.setCenter(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
	this->window->setView(this->view);
	this->updateTextObjects();
	if(this->questionQuit || this->questionSave)
		this->questionWindow->update(this->mousePosView);
}
//#################################     ќ“–»—ќ¬ ј      #################################

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->locations[this->currentLocation]->render(*target);

	if (!this->paused)//отрисовка меню паузы
	{
		
		if (this->currentLocation == "START_LOCATION")
		{
			this->teleportOnFirst->render(*target);
			this->player->render(*target);
			this->npcWoman->render(*target);
			if(!this->startMission->isComplited())
				target->draw(this->signSprite);

		}
		else if (this->currentLocation == "SECOND_LOCATION")
		{
			this->teleportOnSecond->render(*target);
			this->player->render(*target);
			this->npcMan->render(*target);
			if (!this->startMission->isComplited() && this->startMission->getStep() >= 1 && this->startMission->getStep() <= 2)
				target->draw(this->signSprite);
		}

		if (this->startMission->isActive() && !this->startMission->isComplited())
		{
			target->draw(this->missionFormSprite);
			target->draw(this->missionText);
		}
		if (this->teleportOnFirst->getInteraction(this->player) || this->teleportOnSecond->getInteraction(this->player)
			|| this->npcMan->getInteraction(this->player) || this->npcWoman->getInteraction(this->player))
			target->draw(this->interactionText);

		target->draw(this->coinsText);
		target->draw(this->coinSprite);
	}
	else 
	{
		this->pmenu->render(*target);
	}
	if (this->questionQuit || this->questionSave)
	{
		this->questionWindow->show(*this->window);
	}
}