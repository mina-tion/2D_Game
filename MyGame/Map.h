#include "Player.h"

class Map
{
private:
	sf::String *TileMap;//массив карты
	sf::Image map_image; 
	sf::Texture map; 
	sf::Sprite s_map; 
	sf::Vector2i maxMapSize;
	std::string file;


	int heightMap;
	int widthMap;
	unsigned gridSizeU;
	float gridSizeF;
	int gridSizeI;

	int fromX;
	int toX;
	int fromY;
	int toY;

public:
	Map(int height_map, int width_map, std::string map_file);
	virtual ~Map();

	const sf::Vector2i getSize();

	void loadMap();
	void render(sf::RenderTarget& target);
	void updateCollision(Player* player);
};

