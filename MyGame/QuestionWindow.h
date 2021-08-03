#ifndef QUESTIONWINDOW_H
#define QUESTIONWINDOW_H
#include "Button.h"
class QuestionWindow
{
private:
	//переменные
	sf::Texture qTexture;
	sf::RectangleShape qForm;
	sf::Text text;
	sf::Font* font;
	sf::RenderTarget* target;
	std::map<std::string, Button*> buttons;

public:
	QuestionWindow(const float sizew_x, const float sizew_y, sf::Font* font, std::string text);
	virtual ~QuestionWindow();

	void initForm(const float sizew_x, const float sizew_y);
	void initButtons(sf::Font* font, float sizew_x, float sizew_y);
	
	void render(sf::RenderTarget& target);
	void show(sf::RenderTarget& target);
	void update(sf::Vector2f mousePosView);
	int checkPressedKey();
	void changeText(std::string text);
};

#endif