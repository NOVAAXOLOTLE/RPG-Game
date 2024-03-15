//
// Created by Samuel Dominguez on 3/14/2024.
//

#include "Player.h"

#include <utility>
#include <iostream>
#include "../Utils.h"

using namespace std;
using namespace combat_utils;

bool compareSpeed(Enemy *a, Enemy *b) {
    return a->getSpeed() > b->getSpeed();
}

Player::Player(string _name, int _health, int _attack, int _defense, int _speed) :
Character(std::move(_name), _health, _attack, _defense, _speed, true) {
    experience = 0;
    level = 1;
}

void Player::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Player::takeDamage(int damage) {
    setHealth(health - damage);
    cout << "You have taken " << damage << " damage" << endl;
    if (health <= 0) {
        cout << "You Died" << endl;
    }
}

Character *Player::getTarget(vector<Enemy *> enemies) {
    cout << "Choose a target" << endl;
    int targetIndex = 0;
    for (int i = 0; i < enemies.size(); i++) {
        cout << i << ". " << enemies[i]->getName() << endl;
    }
    cin >> targetIndex;
    //TODO: Add input validation
    return enemies[targetIndex];
}

void Player::flee(vector<Enemy *> enemies) {
    sort(enemies.begin(), enemies.end(), compareSpeed);
    Enemy *fastestEnemy = enemies[0];
    bool fled = false;
    if (this->getSpeed() > fastestEnemy->getSpeed()) {
        fled = true;
    } else {
        srand(time(nullptr));
        int chance = rand() % 100;
        cout << "chance: " << chance << endl;
        fled = chance > 97;
    }

    this->fled = fled;
}

[[maybe_unused]] void Player::emote() {
    cout << "*You just have been Get Griddy-ed*" << endl;
}

void Player::levelUp() {
    level++;
    setHealth(getHealth() + 10);
    setAttack(getAttack() + 5);
    setDefense(getDefense() + 5);
    setSpeed(getSpeed() + 5);
}

[[maybe_unused]] void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 0;
    }
}

Action Player::takeAction(const vector<Enemy *> &enemies) {
    int option = 0;
    cout << "Choose an action" << endl;
    cout << "1.- Attack" << endl;
    cout << "2.- Flee" << endl;
    cin >> option;
    Character *target = nullptr;

    //This variable saves
    //1.- What I'm going to do?
    //2.- With which velocity/priority?
    Action myAction;

    myAction.speed = this->getSpeed();
    myAction.subscriber = this;

    switch (option) {
        case 1:
            target = getTarget(enemies);
            myAction.target = target;
            myAction.action = [this, target]() {
                doAttack(target);
            };
            break;
        case 2:
            myAction.action = [this, enemies] {
                flee(enemies);
            };
            break;
        default:
            cout << "Invalid option" << endl;
            break;
    }

    return myAction;
}

