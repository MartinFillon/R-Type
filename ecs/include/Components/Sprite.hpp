/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <string>

#define PLAYER_SPRITE "r-typesheet42.gif"
#define WEAPON_SPRITE "r-typesheetGun.gif"
#define ENNEMIES_WEAPON_SPRITE "r-typesheetEnnemiesShoot.gif"
#define BASIC_ENNEMIES_SPRITE "r-typesheet5.gif"
#define FIRST_BOSS_SPRITE "r-typesheet32.gif"
#define BACKGROUND1_SPRITE "Background/background_1.png"
#define BACKGROUND2_SPRITE "Background/background_2.png"
#define BACKGROUND3_SPRITE "Background/background_3.png"
#define BACKGROUND4_SPRITE "Background/background_4.png"

namespace ecs {
    namespace component {
        struct Sprite {
            std::string _pathToSprite;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !SPRITE_HPP_ */
