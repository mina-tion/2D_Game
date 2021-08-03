#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite &sprite, 
	float maxVelocity, float acceleration, float deceleration)
	:sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
}

MovementComponent::~MovementComponent()
{
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float &dt)
{
	//ускорение спрайта до тех пор, пока не достигнет максимальной скорости
	this->velocity.x += this->acceleration * dir_x;
	this->velocity.y += this->acceleration * dir_y;

}

void MovementComponent::update(const float& dt)
{
	decelerations(this->velocity.x);
	decelerations(this->velocity.y);
	this->sprite.move(this->velocity* dt);
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case movement_states::IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;
		break;
	case movement_states::MOVING:
		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;
		break;
	case movement_states::MOVING_LEFT:
		if (this->velocity.x < 0.f)
			return true;
		break;
	case movement_states::MOVING_RIGHT:
		if (this->velocity.x > 0.f)
			return true;
		break;
	case movement_states::MOVING_UP:
		if (this->velocity.y < 0.f)
			return true;
		break;
	case movement_states::MOVING_DOWN:
		if (this->velocity.y > 0.f)
			return true;
		break;
	}

	return false;
}

void MovementComponent::stopVelocity()
{
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	this->velocity.y = 0.f;
}

void MovementComponent::decelerations(float& value)
{
	if (value > 0.f)//проверка пол.
	{
		//проверка макс. скорости
		if (value > this->maxVelocity)
			value = this->maxVelocity;

		//торможение
		value -= deceleration;
		if (value < 0.f)
			value = 0.f;
	}
	else if (value < 0.f)//проверка отр.
	{
		//проверка макс. скорости
		if (value < -this->maxVelocity)
			value = -this->maxVelocity;

		value += deceleration;
		if (value > 0.f)
			value = 0.f;
	}


}