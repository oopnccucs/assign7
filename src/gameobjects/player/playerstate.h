#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

namespace PlayerState
{
    enum MoveState {
        // continue moving
        MOVE,

        // move to the left room
        LEFTROOM,

        // move to the right room
        RIGHTROOM,
    };
} // namespace PlayerState

#endif