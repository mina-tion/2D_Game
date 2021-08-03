#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicSettings::GraphicSettings()
{
	this->title = "Default";
	this->resolution = sf::VideoMode(1360, 786);
	this->fullscreen = false;
	this->verticalSync = false;
	this->frameRateLimit = 120;
	this->contextSettings.antialiasingLevel = 0;
}

void GraphicSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << this->title;
		ofs << this->resolution.width << " " << this->resolution.height;
		ofs << this->fullscreen;
		ofs << this->frameRateLimit;
		ofs << this->verticalSync;
		ofs << this->contextSettings.antialiasingLevel;
	}

	ofs.close();
}

void GraphicSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->fullscreen;
		ifs >> this->frameRateLimit;
		ifs >> this->verticalSync;
		ifs >> this->contextSettings.antialiasingLevel;
	}

	ifs.close();
}