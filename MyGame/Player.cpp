#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->coins = 100;
	
}
void Player::initComponents()
{
}

Player::Player(float x, float y, sf::Texture &texture_sheet)
{
	this->initVariables();
	this->setPosition(x, y);
	this->createHitboxComponent(this->sprite, 28.f, 20.f, 22.f, 55.f);

	this->createMovementComponent(200.f, 10.f, 5.f);
	this->createAnimationComponent(texture_sheet);
	this->animationComponent->addAnimation("IDLE",      10.f, 4, 0, 4, 0, 77, 77);
	this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 1, 7, 1, 77, 77);
	this->animationComponent->addAnimation("WALK_UP",   10.f, 0, 3, 7, 3, 77, 77);
	this->animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 0, 7, 0, 77, 77);
}

Player::~Player()
{
}

const int Player::getCoins()
{
	return this->coins;
}

void Player::setCoins(int coins)
{
	this->coins = coins;
}

void Player::changeCoins(int coins)
{
	this->coins += coins;
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	if (this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE", dt);
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(1.f, 1.f);
		this->animationComponent->play("WALK_LEFT", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(77.f, 0.f);
		this->sprite.setScale(-1.f, 1.f);
		this->animationComponent->play("WALK_LEFT", dt);
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt);
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt);
	}
	
	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	this->hitboxComponent->render(target);
}

const std::string Player::getMoveDirection()
{
	if (this->movementComponent->getState(MOVING_LEFT))
	{
		return "LEFT";
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		return "RIGHT";
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		return "UP";
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		return "DOWN";
	}

	return "IDLE";
}


