//
// Created by Samuel Dominguez on 3/14/2024.
//

#ifndef RPG_GAME_PLAYER_H
#define RPG_GAME_PLAYER_H

#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"

struct Action;
class Enemy;

class Player: public Character {
protected:
    int experience;
    int level;
public:
    Player(string _name, int _health, int _attack, int _defense, int _speed);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;

    static Character* getTarget(vector<Enemy*> enemies);

    void flee(vector<Enemy*> enemies);

    [[maybe_unused]] static void emote();
    void levelUp();

    [[maybe_unused]] void gainExperience(int);

    Action takeAction(const vector<Enemy*>& enemies);
};


#endif //RPG_GAME_PLAYER_H
