#include "stdafx.h"
#include "QuestionWindow.h"

QuestionWindow::QuestionWindow(const float sizew_x, const float sizew_y, sf::Font* font, std::string text)
{
	this->target = NULL;
	initForm(sizew_x, sizew_y);
	initButtons(font, sizew_x, sizew_y);
	
	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(20);

	this->text.setPosition(this->qForm.getPosition().x + (this->qForm.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
							this->qForm.getPosition().y + (this->qForm.getGlobalBounds().height /4.f) - this->text.getGlobalBounds().height / 2.f);
}
void QuestionWindow::changeText(std::string text)
{
	this->text.setString(text);
}

QuestionWindow::~QuestionWindow()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void QuestionWindow::initForm(const float sizew_x, const float sizew_y)
{
	this->qForm.setSize(sf::Vector2f(sizew_x/2.5f, sizew_y/3.f));

	if (!this->qTexture.loadFromFile("Resourses/Images/question.png"))
	{
		throw"ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->qForm.setTexture(&this->qTexture);
	this->qForm.setPosition(sizew_x / 3.2f, sizew_y / 3.f);

}

void QuestionWindow::initButtons(sf::Font* font, float sizew_x, float sizew_y)
{
	this->buttons["YES"] = new Button(this->qForm.getPosition().x + (this->qForm.getGlobalBounds().width/ 8.f), //позиция по х
									  this->qForm.getPosition().y + (this->qForm.getGlobalBounds().height / 2.f), //позиция по у
									  this->qForm.getGlobalBounds().width / 3.8f, 60,//ширина и высота
									  font, "Yes",  
									  sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["NO"] = new Button(this->qForm.getPosition().x + (this->qForm.getGlobalBounds().width / 1.6f), //позиция по х
									 this->qForm.getPosition().y + (this->qForm.getGlobalBounds().height / 2.f), //позиция по у
									 this->qForm.getGlobalBounds().width / 3.8f, 60,//ширина и высота
											font, "No",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}


void QuestionWindow::show(sf::RenderTarget& target)
{
	if (!this->target)
		this->target = &target;
	render(*this->target);
}

void QuestionWindow::update(sf::Vector2f mousePosView)
{
	//Обновление всех кнопок в игре и нажатий
	for (auto& it : this->buttons)
	{
		it.second->update(mousePosView);
	}

	this->text.setPosition(this->qForm.getPosition().x + (this->qForm.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->qForm.getPosition().y + (this->qForm.getGlobalBounds().height / 4.f) - this->text.getGlobalBounds().height / 2.f);

	checkPressedKey();
}

int QuestionWindow::checkPressedKey()
{
	if (buttons["YES"]->isPressed())
		return 1;
	if (buttons["NO"]->isPressed())
		return 2;
	return 0;
}


void QuestionWindow::render(sf::RenderTarget& target)
{
	target.draw(this->qForm);
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
	target.draw(this->text);
}

