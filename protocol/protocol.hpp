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

enum Movements {
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

enum Operations {
    OBJECT_POSITION = 1,
    NEW_OBJECT,
    MOVE,
    SHOOT,
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
    OBJECT_INFORMATIONS
};

const uint32_t MAGIC = 0x42454552;
const std::string MAGIC = "BEER";

}; // namespace protocol
