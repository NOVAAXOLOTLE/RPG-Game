//
// Created by Samuel Dominguez on 3/14/2024.
//

#include "Combat.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants);
    for(auto participant : participants) {
        if (participant->getIsPlayer()) {
            partyMembers.push_back((Player*)participant);
        }
        else {
            enemies.push_back((Enemy*)participant);
        }
    }
}

Combat::Combat(vector<Player *> _partyMembers, vector<Enemy *> _enemies) {
    partyMembers = std::move(_partyMembers);
    enemies = std::move(_enemies);
}

Combat::Combat() {
    participants = vector<Character*>();
}

void Combat::prepareCombat() {
    sort(participants.begin(), participants.end(), compareSpeed);
}

void Combat::registerActions() {
    auto participant = participants.begin();

    //An iteration for every participant (player and enemy)
    while (participant != participants.end()) {
        Action currentAction;
        if ((*participant)->getIsPlayer()) {
            currentAction = ((Player*)*participant)->takeAction(enemies);
        }
        else {
            currentAction = ((Enemy*)*participant)->takeAction(partyMembers);
        }
        actions.push(currentAction);
        participant++;
    }
}

void Combat::executeActions() {
    //Here is where the actions are executed
    while(!actions.empty()) {
        Action currentAction = actions.top();
        currentAction.action();
        checkForFlee(currentAction.subscriber);
        checkParticipantStatus(currentAction.subscriber);
        checkParticipantStatus(currentAction.target);
        actions.pop();
    }
}

void Combat::checkParticipantStatus(Character *participant) {
    if (participant->getHealth() <= 0) {
        if (participant->getIsPlayer()) {
            partyMembers.erase(remove(partyMembers.begin(), partyMembers.end(), participant), partyMembers.end());
        }
        else {
            gainReward(participant);
            enemies.erase(remove(enemies.begin(), enemies.end(), participant), enemies.end());
        }
        participants.erase(remove(participants.begin(), participants.end(), participant), participants.end());
    }
}

void Combat::gainReward(Character *participant) {
    int exp = 0;
    exp = participant->getExpReward();

    partyMembers[0]->gainExperience(exp);
    if (partyMembers[0]->isLeveledUp()) {
        for (int i = 0; i < enemies.size(); ++i) {
            if (enemies[i] != participant) {
                enemies[i]->uploadStatistics();
            }
        }
        partyMembers[0]->setLeveledUp(false);
    }
}

void Combat::checkForFlee(Character *character) {
    bool fled = character->hasFled();
    if (fled) {
        if (character->getIsPlayer()) {
            cout << "You have fled the combat" << endl;
            partyMembers.erase(remove(partyMembers.begin(), partyMembers.end(), character), partyMembers.end());
        }
        else {
            cout << character->getName() << "has fled the combat" << endl;
            enemies.erase(remove(enemies.begin(), enemies.end(), character), enemies.end());
        }
        participants.erase(remove(participants.begin(), participants.end(), character), participants.end());
    }
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if (participant->getIsPlayer()) {
        partyMembers.push_back((Player*)participant);
    }
    else {
        enemies.push_back((Enemy*)participant);
    }
}

void Combat::doCombat() {
    prepareCombat();

    while(!enemies.empty() && !partyMembers.empty()) {
        registerActions();
        executeActions();
    }

    if (enemies.empty()) {
        cout << "You have won the combat" << endl;
    }
    else {
        cout << "You Lose - Game Over" << endl;
    }
}

string Combat::participantsToString() {
    string result;
    for (auto & participant : participants) {
        result += participant->toString() + "\n";
    }
    return result;
}