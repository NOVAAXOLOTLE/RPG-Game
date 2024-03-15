//
// Created by SADM-PC on 3/14/2024.
//

#ifndef RPG_GAME_UTILS_H
#define RPG_GAME_UTILS_H
#include <cstdlib>
#include <ctime>

namespace combat_utils {
    int getRolledAttack(int attack) {
        srand(time(nullptr));
        int lowerLimit = attack * .80;
        return (rand() % (attack - lowerLimit)) + lowerLimit;
    }
}
#endif //RPG_GAME_UTILS_H
