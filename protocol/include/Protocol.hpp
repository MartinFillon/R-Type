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
        OBJECTSTYPES_FIRST = -1, // must be at the begining of the enum
        PLAYER_1,
        PLAYER_2,
        PLAYER_3,
        PLAYER_4,
        ENEMY,
        BULLET,
        TEXT,
        BONUS,
        MILESPATES,
        BOSS,
        OBJECTSTYPES_LENGTH, // must be at the end of the enum
    };

    enum Direction {
        DIRECTION_FIRST = -1, // must be at the begining of the enum
        UP,
        RIGHT,
        DOWN,
        LEFT,
        Space,
        DIRECTION_LENGTH, // must be at the end of the enum
    };

    enum Operations {
        OPERATIONS_FIRST = -1, // must be at the begining of the enum
        OBJECT_POSITION,
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
        OPERATIONS_LENGTH, // must be at the end of the enum
    };

    const uint32_t MAGIC = 0x42454552;

    enum Events {
        EVENTS_FIRST = 0, // must be at the begining of the enum
        MOVE,
        SHOOT,
        EVENTS_LENGTH, // must be at the end of the enum
    };

}; // namespace protocol
