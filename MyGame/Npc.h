#pragma once
#include "Player.h"
class Npc :
    public Entity
{
private:

public:
    Npc(float x, float y, sf::Texture& texture_sheet);
    virtual ~Npc();

    const bool getInteraction(Player* player);
    //const sf::FloatRect getGlobalBounds() const;
    //функции
    void update(const float& dt);
    void render(sf::RenderTarget& target);
};

