//
// Created by Samuel Dominguez on 3/14/2024.
//

#ifndef RPG_GAME_ACTION_H
#define RPG_GAME_ACTION_H
#include <functional>
#include "../Character/Character.h"

class Character;

struct Action {
    int speed = 0;
    [[maybe_unused]] Character* subscriber = nullptr;
    Character* target = nullptr;
    std::function<void(void)> action = nullptr;

    Action(std::function<void(void)> _action, int _speed, Character* _subscriber, Character* _target) {
        action = std::move(_action);
        speed = _speed;
        subscriber = _subscriber;
        target = _target;
    }
    Action()= default;

    bool operator<(const Action& p) const
    {
        return this->speed < p.speed;
    }
};

#endif //RPG_GAME_ACTION_H
