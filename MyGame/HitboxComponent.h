#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;
	sf::FloatRect nextPosition;

public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	virtual ~HitboxComponent();

	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f&  velocity);

	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);


	bool intersects(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);

};
#endif
