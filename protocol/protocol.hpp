/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** protocol
*/

#pragma once

#include <string>

namespace protocol {

    enum ObjectTypes {
        PLAYER_SELF,
        PLAYER_1,
        PLAYER_2,
        PLAYER_3,
        ENEMY,
        BULLET,
        BACKGROUND,
        FOREGROUND,
    };

    enum Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT,
    };

    enum Operations {
        OBJECT_POSITION = 1,
        NEW_OBJECT = 2,
        EVENT = 3,
        GAME_SPEED = 4,
        OBJECT_REMOVED = 5,
        NEW_PLAYER = 6,
        PLAYER_CRASHED = 7,
        LEAVING = 8,
        PLAYER_LEFT = 9,
        WELCOME = 10,
        REFUSED = 11,
        READY = 12,
        PING = 13,
        OBJECT_INFORMATIONS = 14
    };

    const uint32_t MAGIC = 0x42454552;

    enum Events { Move = 1, Shoot };

}; // namespace protocol
