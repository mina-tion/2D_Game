#include "stdafx.h"
#include "Teleport.h"

Teleport::Teleport(float x, float y, sf::Texture& texture_sheet)
{
	this->setPosition(x, y);
	this->createHitboxComponent(this->sprite, -93.f, 10.f, 58.f, 30.f);
	this->createAnimationComponent(texture_sheet);
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 0, 0, 64, 128);
	this->animationComponent->addAnimation("INTERACTION", 10.f, 1, 0, 4, 0, 64, 128);
}

Teleport::~Teleport()
{
}

void Teleport::update(const float& dt)
{
	this->sprite.setRotation(90);
	this->animationComponent->play("IDLE", dt);
	this->hitboxComponent->update();
}

void Teleport::updateAnimation(const float& dt)
{
	this->sprite.setRotation(90);
	this->animationComponent->play("INTERACTION", dt);
	this->hitboxComponent->update();
}

void Teleport::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	this->hitboxComponent->render(target);
}

const bool Teleport::getInteraction(Player* player)
{
	if (this->getGlobalBounds().intersects(player->getGlobalBounds()))
		return true;
	return false;
}
