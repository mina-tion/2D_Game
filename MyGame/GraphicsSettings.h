#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H


class GraphicSettings
{
public:
	//����������
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;


	GraphicSettings();
	//�������
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};
#endif