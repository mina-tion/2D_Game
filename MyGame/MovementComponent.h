#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponent
{
private:

	sf::Sprite &sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;
	//иницилизация

public: 
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();
	
	const sf::Vector2f& getVelocity() const;

	//функции
	const bool getState(const short unsigned state) const;

	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	void decelerations(float& value);
	void move(const float x, const float y, const float& dt);
	void update(const float& dt);


};

#endif