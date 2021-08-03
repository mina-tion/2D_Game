#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"


class Player: public Entity
{
private:
    //����������
    int coins;

    //�������������
    void initVariables();
    void initComponents();


public: 
    Player(float x, float y, sf::Texture &texture_sheet);
    virtual ~Player();

    const int getCoins();

    //�������
    void setCoins(int coins);
    void changeCoins(int coins);
    void update(const float& dt);
    void render(sf::RenderTarget& target);
    const std::string getMoveDirection();
};

#endif