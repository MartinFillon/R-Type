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
        PLAYER_1 = 1,
        PLAYER_2,
        PLAYER_3,
        PLAYER_4,
        ENEMY,
        BULLET,
        TEXT,
        BONUS,
    };

    enum Direction {
        UP = 0,
        RIGHT,
        DOWN,
        LEFT,
    };

    enum Operations {
        OBJECT_POSITION = 1,
        NEW_OBJECT,
        EVENT,
        GAME_SPEED,
        OBJECT_REMOVED,
        NEW_PLAYER,
        PLAYER_CRASHED,
        LEAVING,
        PLAYER_LEFT,
        WELCOME,
        REFUSED,
        READY,
        PING,
        OBJECT_INFORMATIONS,
    };

    const uint32_t MAGIC = 0x42454552;

    enum Events {
        Move = 1,
        Shoot,
    };

}; // namespace protocol
