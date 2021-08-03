#include "stdafx.h"
#include "Game.h"

Game::Game()
{
    this->initVariables();
    this->initGraphicSettings();
	this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
    
}

Game::~Game()
{
	delete this->window;
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}
//запуск игры
void Game::run()
{
    while (window->isOpen())
    {
        updateDt();
        update();
        render();
    }
}

void Game::endApplication()
{

}

//функции
void Game::updateDt()
{   //обновление переменной dt с указание времени, которе уходит на отрисовку и обновление кадра
	this->dt = this->dtClock.restart().asSeconds();

}
void Game::updateSfEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        switch (this->sfEvent.type)
        {
        case sf::Event::Closed:

            this->window->close();
            break;
        }
    }
}

void Game::update()
{
	this->updateSfEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);
        if (this->states.top()->getQuit())
        { 
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }

    }
    //Заканчивает выполняться
    else 
    {
        this->endApplication();
        this->window->close();
    }

}

void Game::render()
{
	this->window->clear(sf::Color(43, 130, 53));

    //отрисовка кадров
    if (!this->states.empty())
        this->states.top()->render();


	this->window->display();
}

void Game::initVariables()
{
    this->window = NULL;
    this->dt = 0.f;
}

void Game::initGraphicSettings()
{
    this->gSettings.loadFromFile("Config/graphics.ini");
}

void Game::initStateData()
{
    this->stateData.window = this->window;
    this->stateData.gSettings = &this->gSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;

}

void Game::initWindow()
{
    if (this->gSettings.fullscreen)
	    this->window = new sf::RenderWindow(
            this->gSettings.resolution, 
            this->gSettings.title, 
            sf::Style::Fullscreen,
            this->gSettings.contextSettings);
    else
        this->window = new sf::RenderWindow(
            this->gSettings.resolution,
            this->gSettings.title,
            sf::Style::Titlebar,
            this->gSettings.contextSettings);

	this->window->setFramerateLimit(this->gSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gSettings.verticalSync);
}

void Game::initKeys()
{
    std::ifstream ifs("Config/supported_keys.ini");
    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;
        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;

        }
    }
    ifs.close();

    for (auto i : this->supportedKeys)
    {
        std::cout << i.first << " " << i.second <<"\n";
    }
   
}

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
}


