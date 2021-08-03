#include "stdafx.h"
#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font,
	std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;
	
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));


	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(20);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f )- this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);


	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

bool Button::isPressed() 
{
	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}

	return false;
}

//функции



void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}


void Button::update(const sf::Vector2f& mousePos)
{
	//обновление состояний наведения и нажатия на кнопку

	//покой
	this->buttonState = BTN_IDLE;

	//наведение
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		//нажатие
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}
