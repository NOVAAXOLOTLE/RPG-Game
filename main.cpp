#include <iostream>
#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Combat/Combat.h"
#include <queue>

int main() {
    string name;
    auto *enemy = new Enemy("Goblin", 20, 4, 2, 7, 15);
    auto *enemy2 = new Enemy("Orc", 30, 5, 3, 2, 30);

    cout << "¿Cual es tu nombre?" << endl;
    cin >> name;

    auto *player = new Player(name, 25, 7, 2, 10);

    vector<Character*> participants;
    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    auto* combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete enemy2;
    delete combat;

    return 0;
}
