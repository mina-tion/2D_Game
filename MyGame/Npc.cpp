#include "stdafx.h"
#include "Npc.h"

Npc::Npc(float x, float y, sf::Texture& texture_sheet)
{
	this->setPosition(x, y);
	this->createHitboxComponent(this->sprite, 28.f, 20.f, 22.f, 55.f);
	this->createAnimationComponent(texture_sheet);
	this->animationComponent->addAnimation("IDLE", 10.f, 4, 0, 4, 0, 77, 77);
}

Npc::~Npc()
{
}

const bool Npc::getInteraction(Player* player)
{
	sf::FloatRect tempBounds = this->getGlobalBounds();

	tempBounds.height += 1;
	tempBounds.left -= 1;
	tempBounds.top -= 1;
	tempBounds.width += 1;

	if (tempBounds.intersects(player->getGlobalBounds()))
	{
		if (player->getMoveDirection() == "LEFT" && player->getGlobalBounds().left == this->getGlobalBounds().left + this->getGlobalBounds().width)
			player->setPosition(this->getPosition().x + this->getGlobalBounds().width, player->getPosition().y);

		if (player->getMoveDirection() == "RIGHT" && player->getGlobalBounds().left + player->getGlobalBounds().width == this->getGlobalBounds().left)
			player->setPosition(this->getPosition().x - this->getGlobalBounds().width, player->getPosition().y);

		if (player->getMoveDirection() == "UP" && player->getGlobalBounds().top == this->getGlobalBounds().top + this->getGlobalBounds().height)
			player->setPosition(player->getPosition().x, this->getPosition().y + this->getGlobalBounds().height);

		if (player->getMoveDirection() == "DOWN" && player->getGlobalBounds().top + player->getGlobalBounds().height == this->getGlobalBounds().top)
			player->setPosition(player->getPosition().x, this->getPosition().y - this->getGlobalBounds().height);
		player->stopVelocity();
		return true;
	}


	return false;
}


void Npc::update(const float& dt)
{
	this->hitboxComponent->update();
}

void Npc::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	this->hitboxComponent->render(target);
}

//const sf::FloatRect Npc::getGlobalBounds() const
//{
//	return this->sprite.getGlobalBounds();
//}