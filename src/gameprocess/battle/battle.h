#ifndef BATTLE_H
#define BATTLE_H

#include "../gameprocess.h"
#include "battlestate.h"

using namespace BattleState;

class Battle: public GameProcessBase {
private:
    Player* player;
    Enemy* enemy;

    BattlePhase state;

    BattleAction actionPlayerSelected;
    BattleAction actionEnemySelected;

    // Please store the damage calculation result in this variable. 
    // The damage will be displayed based on this variable when rendering.
    int damageToPlayer;
    int damageToEnemy;

    static int damageCalculate(BattleAction attackerAction, BattleAction targetAction, int damage);

    static std::string BattleActionToString(BattleAction action);
    
public:
    Battle(Player* player, Enemy* enemy);
    ~Battle();

    ProcessInfo run(InputState action);

    void render();
};

#endif