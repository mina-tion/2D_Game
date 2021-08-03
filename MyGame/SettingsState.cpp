#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		));

	this->background.setPosition(0.f, 0.f);

	if (!this->backgroundTexture.loadFromFile("Resourses/Images/Backgrounds/bg2.png"))
	{
		throw"ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("fonts/GOTHIC.TTF"))
	{
		throw("ERROR::MAIMMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingsState::initText()
{
	this->fullscreenText.setFont(this->font);
	this->fullscreenText.setFillColor(sf::Color(255, 255, 255, 200));
	this->fullscreenText.setCharacterSize(50);
	this->fullscreenText.setString("Fulscreen");
	this->fullscreenText.setPosition(50, 120);

}

void SettingsState::initKeybinds()
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

void SettingsState::initButtons()
{
	this->buttons["FULLSCREEN"] = new Button(300.f, 100.f, 60.f, 60.f, &this->font, "On",
		sf::Color(100, 100, 100, 200), sf::Color(300, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["NO_FULLSCREEN"] = new Button(300.f, 200.f, 60.f, 60.f, &this->font, "Off",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["QUIT"] = new Button(150.f, 600.f, 300.f, 60.f, &this->font, "Back",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

SettingsState::SettingsState(StateData* state_data)
	:State(state_data)
{
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initKeybinds();
	this->initButtons();
	this->view.setCenter(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void SettingsState::updateInput(const float& dt)
{
	//this->checkForQuit();
}

void SettingsState::updateButtons()
{
	//Обновление всех кнопок в игре и нажатий
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//Проверка на выход
	if (this->buttons["QUIT"]->isPressed())
	{
		this->endState();
	}

	if (this->buttons["FULLSCREEN"]->isPressed()&& !this->stateData->gSettings->fullscreen)
	{
		this->stateData->gSettings->fullscreen = true;
		this->window->create(this->stateData->gSettings->resolution, this->stateData->gSettings->title, sf::Style::Fullscreen);
	}

	if (this->buttons["NO_FULLSCREEN"]->isPressed() && this->stateData->gSettings->fullscreen)
	{
		this->stateData->gSettings->fullscreen = false;
		this->window->create(this->stateData->gSettings->resolution, this->stateData->gSettings->title, sf::Style::Titlebar);
	}
}

void SettingsState::update(const float& dt)
{

	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
	window->setView(this->view);
}

void SettingsState::renderButtons(sf::RenderTarget& target)
{

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	target->draw(this->fullscreenText);
	this->renderButtons(*target);
	

}
