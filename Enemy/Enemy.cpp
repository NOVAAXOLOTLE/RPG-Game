//
// Created by Samuel Dominguez on 3/14/2024.
//

#include "Enemy.h"
#include <iostream>

using namespace std;

int getRolledAttack(int attack) {
    srand(time(nullptr));
    int lowerLimit = attack * .80;
    return (rand() % (attack - lowerLimit)) + lowerLimit;
}

bool compareSpeed(Player *a, Player *b) {
    return a->getSpeed() > b->getSpeed();
}

Enemy::Enemy(string name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense, speed, false){
}

void Enemy::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Enemy::takeDamage(int damage) {
    setHealth(getHealth() - damage);
    if (getHealth() <= 0) {
        cout << getName() << " has died" << endl;
    } else {
        cout << getName() << " has taken " << damage << " damage" << endl;
    }
}

void Enemy::flee(vector<Player *> partyMembers) {
    sort(partyMembers.begin(), partyMembers.end(), compareSpeed);
    Player *fastestPlayer = partyMembers[0];
    bool fled = false;
    if (this->getSpeed() > fastestPlayer->getSpeed()) {
        fled = true;
    } else {
        srand(time(nullptr));
        int chance = rand() % 100;
        cout << "chance: " << chance << endl;
        fled = chance > 95;
    }

    this->fled = fled;
}

Character *Enemy::getTarget(vector<Player *> partyMembers) {
    //Obtains the lowest health party member
    int targetIndex = 0;
    int lowestHealth = INT_MAX;
    for (int i = 0; i < partyMembers.size(); i++) {
        if (partyMembers[i]->getHealth() < lowestHealth) {
            lowestHealth = partyMembers[i]->getHealth();
            targetIndex = i;
        }
    }

    return partyMembers[targetIndex];
}

Action Enemy::takeAction(const vector<Player *> &player) {
    Action myAction;
    myAction.speed = getSpeed();
    myAction.subscriber = this;
    Character* target = nullptr;

    if (getHealth() <= (getHealth() * .15)) {
        myAction.action = [this, player]() {
            flee(player);
        };
    } else {
        target = getTarget(player);
        myAction.target = target;
        myAction.action = [this, target]() {
            doAttack(target);
        };
    }

    return myAction;
}
