#pragma once
#include "Entity.h"
#include "Player.h"
class Teleport :
    public Entity
{
private:

public:
    Teleport(float x, float y, sf::Texture& texture_sheet);
    virtual ~Teleport();

    //функции
    void update(const float& dt);
    void updateAnimation(const float& dt);
    void render(sf::RenderTarget& target);
    const bool getInteraction(Player* player);
};

