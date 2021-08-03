#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	//фон
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x),
			static_cast<float>(window.getSize().y)
		));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));
	this->background.setPosition(0.f, 00.f);


	//контейнер
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x) / 3.f,
			static_cast<float>(window.getSize().y) - 80.f
		));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f, 
		40.f);

	//текст
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(50);
	this->menuText.setString("PAUSE MENU");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 40.f);

}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	//delete questionWindow;
}

std::map<std::string, Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

const bool PauseMenu::isButtonPressed(const std::string key) 
{
	return this->buttons[key]->isPressed();
}


void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 300.f;
	float height = 60.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;


	this->buttons[key] = new Button(
		x, y, width, height,
		&this->font, text,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), 	sf::Color(20, 20, 20, 200));
}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	target.draw(this->menuText);
}
