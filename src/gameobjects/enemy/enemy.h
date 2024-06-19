#ifndef ENEMY_H
#define ENEMY_H

#include "../../gamecore/gamestate.h"
#include "../gameobject.h"
#include <string>

class Enemy: public GameObject {
private:
    bool lastBoss = false;
public:
    Enemy(Position initialPosition, int health, int attack, std::string name);
    Enemy(Position initialPosition, int health, int attack, std::string name, bool isLastBoss);
    virtual ~Enemy();

    // return the next position of the enemy that will be moved
    virtual Position nextPosition() = 0;

    virtual void move(InputState action) = 0;

    // When the defeated enemy is the last boss, the game is cleared.
    // Whether an enemy is the last boss is defined by a parameter passed to the Enemy constructor.
    bool isLastBoss();
    
    virtual void render() = 0;
};

#endif