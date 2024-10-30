/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Defs
*/

#pragma once

#define CONFIG_BACKGROUND_0 "./config/background/background.json"
#define CONFIG_BACKGROUND_2 "./config/background/background_2.json"
#define CONFIG_BACKGROUND_3 "./config/background/background_3.json"
#define CONFIG_BACKGROUND_4 "./config/background/background_4.json"

#define CONFIG_PLAYER_0 "./config/player0.json"
#define CONFIG_PLAYER_1 "./config/player1.json"
#define CONFIG_PLAYER_2 "./config/player2.json"
#define CONFIG_PLAYER_3 "./config/player3.json"

#define CONFIG_ENNEMIES "./config/ennemies.json"
#define CONFIG_MILEPATES "./config/milepates.json"
#define CONFIG_BOSS "./config/boss.json"
#define CONFIG_PROJECTILE "./config/projectile.json"
#define CONFIG_PLAYER_PROJECTILE "./config/playerProjectile.json"

#define ENTITY_MANAGER_ERROR_OUT_OF_RANGE "Out of range"

#define SECONDS_TO_MILISECONDS 1000
#define SECONDS_TO_MICROSECONDS 1000000

#define PLAYER_SPRITE "assets/sprites/r-typesheet42.gif"
#define WEAPON_SPRITE "assets/sprites/r-typesheetGun.gif"
#define ENNEMIES_WEAPON_SPRITE "assets/sprites/r-typesheetEnnemiesShoot.gif"
#define BASIC_ENNEMIES_SPRITE "assets/sprites/r-typesheet5.gif"
#define FIRST_BOSS_SPRITE "assets/sprites/r-typesheet32.gif"
#define BACKGROUND1_SPRITE "assets/sprites/Background/background_1.png"
#define BACKGROUND2_SPRITE "assets/sprites/Background/background_2.png"
#define BACKGROUND3_SPRITE "assets/sprites/Background/background_3.png"
#define BACKGROUND4_SPRITE "assets/sprites/Background/background_4.png"

#define BOSS_SPEED 5
#define BOSS_SPAWN_TIME 60
#define BOSS_PROJECTILE_SPEED 5
#define MOVING_PROJECTILE_SPEED 0.01
#define BOSS_PROJECTILE_SPAWN_TIME 3
#define BOSS_SHOOTING_ELAPSED_TIME 0.5

#define PROJECTILE_CLOSE 200
#define PROJECTILE_PADDING 100

#define ENNEMIES_TICK 2

#define MAX_RANDOM_ENNEMIES 4
#define VALUE_SPAWN_ENNEMIES 2

#define BASIC_POS_SPAWN_X 1944
#define MAX_SPAWN_X 2500

#define SHOOTING_ELAPSED_TIME 0.2

#define BASIC_ENNEMIES_ANIMATON_SPEED 0.24
#define BASIC_ENNEMIES_SPEED 1.8
#define BASIC_ENNEMIES_PROJECTILE_SPEED 10
#define BASIC_PROJECTILE_SPEED_TICK 0.3
#define CENTERED_SHOOT 15
#define BASIC_ENNEMIES_SPEED_TICK 8

#define WIDTH_MAX_LIMIT 2700
#define HEIGHT_MAX_LIMIT 2500

#define WIDTH_MIN_LIMIT -300
#define HEIGHT_MIN_LIMIT -300

#define R_ERROR_FILE_NOT_FOUND(file) "File not found on: [" + file + "]"
#define ERROR_PARSING_ERROR(file) "Parsing Error on : [" + file + "]"
