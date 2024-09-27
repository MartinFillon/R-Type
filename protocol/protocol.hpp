/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** protocol
*/

#pragma once

#include <string>

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
    CONNECTING = 42,
    CONNECTED = 1,
    IMAGE,
    OBJECT_POSITION,
    NEW_OBJECT,
    MOVE,
    SHOOT,
    GAME_SPEED,
};

const uint32_t MAGIC = 0x42454552;
