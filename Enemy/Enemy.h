//
// Created by Samuel Dominguez on 3/14/2024.
//

#ifndef RPG_GAME_ENEMY_H
#define RPG_GAME_ENEMY_H

#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Combat/Action.h"

struct Action;
class Player;

class Enemy: public Character{
public:
    Enemy(string, int, int, int, int);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;

    void flee(vector<Player*> partyMembers);
    Character* getTarget(vector<Player*> partyMembers);
    Action takeAction(const vector<Player*>& player);
};

#endif //RPG_GAME_ENEMY_H
