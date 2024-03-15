//
// Created by Samuel Dominguez on 3/14/2024.
//

#include <string>
#include "Character.h"

using namespace std;

Character::Character(string _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer) {
    name = _name;
    health = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
    fled = false;
}

string Character::getName() {
    return name;
}

void Character::setName(string _name) {
    Character::name = std::move(_name);
}

int Character::getHealth() {
    return health;
}

void Character::setHealth(int _health) {
    Character::health = _health;
}

int Character::getAttack() {
    return attack;
}

void Character::setAttack(int _attack) {
    Character::attack = _attack;
}

int Character::getDefense() {
    return defense;
}

void Character::setDefense(int _defense) {
    Character::defense = _defense;
}

int Character::getSpeed() {
    return speed;
}

void Character::setSpeed(int _speed) {
    Character::speed = _speed;
}

string Character::toString() {
    return "Name: " + name + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed);
}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::hasFled() {
    return fled;
}