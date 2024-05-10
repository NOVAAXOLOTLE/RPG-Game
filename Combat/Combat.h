//
// Created by Samuel Dominguez on 3/14/2024.
//

#ifndef RPG_GAME_COMBAT_H
#define RPG_GAME_COMBAT_H
#pragma once

#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "Action.h"
#include <queue>

using namespace std;

class Combat {
private:
    vector<Character*> participants;
    vector<Player*> partyMembers;
    vector<Enemy*> enemies;
    //Priority's queue of actions
    priority_queue<Action> actions;

    void prepareCombat();
    void registerActions();
    void executeActions();

    void checkParticipantStatus(Character* participant);
    void checkForFlee(Character* character);
    void gainReward(Character *participant);

public:
    explicit Combat(vector<Character*> _participants);
    Combat(vector<Player*> _partyMembers, vector<Enemy*> _enemies);
    Combat();

    void addParticipant(Character *participant);
    void doCombat();
    string participantsToString();
};


#endif //RPG_GAME_COMBAT_H
