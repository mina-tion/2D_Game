#include "stdafx.h"
#include "MainMenuState.h"
#include "Button.h"

MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data) 
{
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initQuestionWindow();

	this->question = false;
	this->view.setCenter(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	delete this->questionWindow;
}

void MainMenuState::initQuestionWindow()
{
	this->questionWindow = new QuestionWindow(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y), 
		&this->font, "Are you sure you want to quit?");
}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
			));
	
	this->background.setPosition(0.f, 0.f);

	if (!this->backgroundTexture.loadFromFile("Resourses/Images/Backgrounds/bg1.png"))
	{
		throw"ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("fonts/GOTHIC.TTF"))
	{
		throw("ERROR::MAIMMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(150.f, 190.f, 300.f, 60.f, &this->font, "New game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["LOAD"] = new Button(150.f, 265.f, 300.f, 60.f, &this->font, "Load",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["SETTINGS_STATE"] = new Button(150.f, 340.f, 300.f, 60.f, &this->font, "Settings",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(150.f, 415.f, 300.f, 60.f, &this->font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}


void MainMenuState::updateInput(const float& dt)
{
	//this->checkForQuit();
}

void MainMenuState::updateButtons()
{
	
	//Обновление всех кнопок в игре и нажатий
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
	//Новая игра
	if (this->buttons["GAME_STATE"]->isPressed() && !this->question)
	{
		this->states->push(new GameState(this->stateData));
	}
	//Настройки
	if (this->buttons["SETTINGS_STATE"]->isPressed() && !this->question)
	{
		this->states->push(new SettingsState(this->stateData));
	}
	//Загрузка
	if (this->buttons["LOAD"]->isPressed())
	{
		std::ofstream ofs;
		ofs.open("Config/saves.ini", std::ios::_Nocreate);

		if (ofs)
		{
			ofs.close();
			this->states->push(new GameState(this->stateData, "Config/saves.ini"));
		}
	}

    //Проверка на выход
	if (this->buttons["EXIT_STATE"]->isPressed()&& !this->question|| 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && !this->question)
	{		this->questionWindow->changeText("Are you sure you want to quit?");
			this->question = true;
	}

	if (this->question)
	{
		//обновление окна и кнопок
		this->questionWindow->update(this->mousePosView);
		if (this->questionWindow->checkPressedKey() == 2)
			this->question = false;
		if (this->questionWindow->checkPressedKey() == 1)
			this->endState();
	}

}


void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);
	this->updateButtons();
	window->setView(this->view);
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);

	this->renderButtons(*target);
	
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y-50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << "  " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);*/

	if (this->question)
	{
		//std::cout << "open";
		this->questionWindow->show(*this->window);
	}
}

