#ifndef BATTLESTATE_H
#define BATTLESTATE_H

namespace BattleState
{
    enum BattlePhase {
        ACTION_SELECTING,
        TURN_END,
        ENEMY_DEAD,
        PLAYER_DEAD
    };

    enum BattleMenuInput {
        MENU_NONE,
        MENU_UP,
        MENU_DOWN,
        MENU_CONFIRM
    };

    enum BattleAction {
        FORCE_ATTACK,
        ATTACK,
        DEFEND,
        HEAL
    };

    const int BATTLE_ACTION_COUNT_PLAYER = 4;
    const int BATTLE_ACTION_COUNT_ENEMY = 3;

    const int FORCE_ATTACK_MULTIPLIER = 2;
    const int DEFEND_MULTIPLIER = 2;
    const int ATTACK_MULTIPLIER = 1;
} // namespace Battle


#endif