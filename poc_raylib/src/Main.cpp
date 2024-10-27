/*******************************************************************************************
*
*   raylib [models] example - Load 3d model with animations and play them
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.5
*
*   Example contributed by Culacant (@culacant) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Culacant (@culacant) and Ramon Santamaria (@raysan5)
*
********************************************************************************************
*
*   NOTE: To export a model from blender, make sure it is not posed, the vertices need to be 
*         in the same position as they would be in edit mode and the scale of your models is 
*         set to 0. Scaling can be done from the export menu.
*
********************************************************************************************/

// #include "raylib.h"
#include <filesystem>
#include <iostream>
#include "Poc.hpp"
int main(void)
{
    try {
        poc::Poc game(60);
        return game.run();
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    // const int screenWidth = 1920;
    // const int screenHeight = 1080;

    // InitWindow(screenWidth, screenHeight, "raylib [models] example - model animation");

    // Camera camera = { 0 };
    // camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    // camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    // camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    // camera.fovy = 45.0f;
    // camera.projection = CAMERA_PERSPECTIVE;

    // Model model = LoadModel("assets/Model/Sub.obj");
    // Texture2D texture = LoadTexture("assets/Sprites/NewSub.png");
    // SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);

    // Vector3 position = { 0.0f, 0.0f, 0.0f };

    // DisableCursor();
    // SetTargetFPS(60);

    // while (!WindowShouldClose())
    // {
    //     UpdateCamera(&camera, CAMERA_FIRST_PERSON);

    //     if (IsKeyDown(KEY_LEFT_CONTROL)) {
    //         camera.position.y -= 1;
    //     }

    //     if (IsKeyDown(KEY_LEFT_SHIFT)) {
    //         camera.position.y += 1;
    //     }

    //     if (IsKeyDown(KEY_O)) {
    //         position.x += 1;
    //     }
    //     if (IsKeyDown(KEY_L)) {
    //         position.x -= 1;
    //     }

    //     BeginDrawing();

    //         ClearBackground(RAYWHITE);

    //         BeginMode3D(camera);

    //             DrawModelEx(model, position, (Vector3){ 1.0f, 0.0f, 0.0f }, 0.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);

    //             DrawGrid(10, 1.0f);

    //         EndMode3D();

    //         DrawText("PRESS SPACE to PLAY MODEL ANIMATION", 10, 10, 20, MAROON);
    //         DrawText("(c) Guy IQM 3D model by @culacant", screenWidth - 200, screenHeight - 20, 10, GRAY);

    //     EndDrawing();
    // }

    // UnloadTexture(texture);
    // UnloadModel(model);

    // CloseWindow();

    // return 0;
}