#include "stdafx.h"
#include "Map.h"

Map::Map(int height_map, int width_map, std::string map_file)
{
	this->heightMap = height_map;
	this->widthMap = width_map;

	this->gridSizeU = 32;
	this->gridSizeF = 32.f;
	this->gridSizeI = 32;

	this->maxMapSize.x = widthMap * gridSizeU;
	this->maxMapSize.y = heightMap * gridSizeU;

	//загрузка тайлов
	this->map_image.loadFromFile("Resourses/Images/Tiles/terrain.png");
	this->map.loadFromImage(map_image); 
	this->s_map.setTexture(map); 

	this->TileMap = new sf::String[this->heightMap];

	this->file = map_file;
	this->loadMap();


	this->fromX = 0;
	this->fromY = 0;
	this->toX = 0;
	this->toY = 0;
}

Map::~Map()
{
	 
}

const sf::Vector2i Map::getSize()
{
	return this->maxMapSize;
}

void Map::loadMap()
{

	std::ifstream ifs(this->file);
	if (ifs.is_open())
	{
		int row = 0;
		std::string key = "";
		while (getline(ifs, key))
		{
			this->TileMap[row] = key;
			row++;
		}
	}
	else 
		std::cout << "file NOYT open";
	ifs.close();
}

void Map::render(sf::RenderTarget& target)
{
	for (int i = 0; i < this->heightMap; i++)
	{
		for (int j = 0; j < this->widthMap; j++)
		{
			if (this->TileMap[i][j] == '0')
				this->s_map.setTextureRect(sf::IntRect(480, 355, this->gridSizeU, this->gridSizeU));//поля
			if (this->TileMap[i][j] == 'g')
				this->s_map.setTextureRect(sf::IntRect(33, 352, this->gridSizeU, this->gridSizeU));//трава_1
			if (this->TileMap[i][j] == 'q')
				this->s_map.setTextureRect(sf::IntRect(0, 192, this->gridSizeU, this->gridSizeU));//трава_2
			if (this->TileMap[i][j] == 't')
				this->s_map.setTextureRect(sf::IntRect(0, 227, this->gridSizeU, this->gridSizeU));//трава_3
			if (this->TileMap[i][j] == ' ')
				this->s_map.setTextureRect(sf::IntRect(125, 285, this->gridSizeU, this->gridSizeU));//земля
			if (this->TileMap[i][j] == 'w')
				this->s_map.setTextureRect(sf::IntRect(576, 0, this->gridSizeU, this->gridSizeU));//источники воды
			if (this->TileMap[i][j] == 'f')
				this->s_map.setTextureRect(sf::IntRect(159, 352, this->gridSizeU, this->gridSizeU));//цветы

			this->s_map.setPosition(static_cast<float>(j) * this->gridSizeF, static_cast<float>(i) * this->gridSizeF);//задает каждому тайлу позицию 
			target.draw(this->s_map);//рисуем квадратики на экран
			
		}
	}
}


void Map::updateCollision(Player* player)//ф-ция взаимодействия с картой
{
	//ОГРАНИЧЕНИЕ ПОЛЕЙ КАРТЫ
	if (player->getPosition().x <= 0.f)
	{
		player->setPosition(0.f, player->getPosition().y);
		player->stopVelocityX();
	}
	else if (player->getPosition().x + player->getGlobalBounds().width >= this->maxMapSize.x)
	{
		player->setPosition(this->maxMapSize.x - player->getGlobalBounds().width, player->getPosition().y);
		player->stopVelocityX();
	}
	if (player->getPosition().y <= 0.f)
	{
		player->setPosition(player->getPosition().x, 0.f);
		player->stopVelocityY();
	}
	else if (player->getPosition().y + player->getGlobalBounds().height >= this->maxMapSize.y)
	{
		player->setPosition(player->getPosition().x, this->maxMapSize.y - player->getGlobalBounds().height);
		player->stopVelocityY();
	}	

	this->fromX = player->getGridPosition(gridSizeI).x;
		if (this->fromX < 0)
			this->fromX = 0;
		else if (this->fromX > this->maxMapSize.x)
			this->fromX = this->maxMapSize.x;

	this->toX = player->getGridPosition(gridSizeI).x + 1;
		if (this->toX < 0)
			this->toX = 0;
		else if (this->toX >= this->maxMapSize.x)
			this->toX = this->maxMapSize.x ;
	this->fromY = player->getGridPosition(gridSizeI).y ;
		if (this->fromY < 0)
			this->fromY = 0;
		else if (this->fromY >= this->maxMapSize.y)
			this->fromY = this->maxMapSize.y - 1;

	this->toY = player->getGridPosition(gridSizeI).y + 1;
		if (this->toY < 0)
			this->toY = 0;
		else if (this->toY >= this->maxMapSize.y)
			this->toY = this->maxMapSize.y - 1;


	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			if (this->TileMap[x][y] == '0')
			{

				if (player->getMoveDirection() == "LEFT")
				{
					player->setPosition(x * gridSizeF + gridSizeF, player->getPosition().y);

				}
				else if (player->getMoveDirection() == "UP")
				{
					player->setPosition(player->getPosition().x, y * gridSizeF + gridSizeF);
				}
				else if (player->getMoveDirection() == "RIGHT")
				{
					player->setPosition((x * gridSizeF - player->getGlobalBounds().width) - 2, player->getPosition().y);
				}
				else if (player->getMoveDirection() == "DOWN")
				{
					player->setPosition(player->getPosition().x, y * gridSizeF - player->getGlobalBounds().height - 2);
				}
				player->stopVelocity();
			}
		}
	}

}