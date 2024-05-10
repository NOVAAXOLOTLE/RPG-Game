//
// Created by Samuel Dominguez on 3/14/2024.
//

#ifndef RPG_GAME_CHARACTER_H
#define RPG_GAME_CHARACTER_H
#include <string>
#include "../Combat/Action.h"

using namespace std;

class Character {
protected:
    string name;
    int health;
    int maxHealth;
    int attack;
    int defense;
    int speed;
    bool isPlayer;
    bool fled;
    int expReward;
public:
    Character(string, int, int, int, int, int, bool);

    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;

    string getName();
    void setName(string);
    int getHealth();
    void setHealth(int);
    int getAttack();
    void setAttack(int);
    int getDefense();
    void setDefense(int);
    int getSpeed();
    void setSpeed(int);
    string toString();
    bool getIsPlayer();
    bool hasFled();
    int getMaxHealth();
    void setMaxHealth(int);

    virtual int getExpReward();
    void setExpReward(int);
};

#endif //RPG_GAME_CHARACTER_H
