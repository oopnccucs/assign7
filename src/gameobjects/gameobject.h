#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../functions/position/position.h"
#include <string>

class GameObject {
private:
    Position position;

    int health;
    int maxHealth;

    std::string name;

    int attack;
public:
    GameObject(Position initialPosition, int maxHealth, int attack, std::string name);

    virtual ~GameObject();

    Position getPosition();

    void setPosition(Position position);

    // get health value of the object
    int getHealth();

    // get max health value of the object
    int getMaxHealth();

    // get attack value of the object
    int getAttack();

    // calculate the damage and reduce the health
    void hurt(int damage);

    std::string getName();

    virtual void render() = 0;
};

#endif