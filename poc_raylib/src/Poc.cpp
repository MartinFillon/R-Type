/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#include <cstdlib>
#include <memory>
#include <raylib.h>
#include <string>
#include <iostream>
#include "Poc.hpp"
#include "Components/Animations.hpp"
#include "Components/Attributes.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Gravitable.hpp"
#include "Components/KeyPressed.hpp"
#include "Components/Model.hpp"
#include "Components/Position3D.hpp"
#include "Components/Rotate.hpp"
#include "Components/Sprite.hpp"
#include "Registry.hpp"
#include "Systems/GravitableThirdDSystem.hpp"
#include "Systems/ThirdDMouvementSystem.hpp"
#include "ZipperIterator.hpp"
#include "raymath.h"

namespace poc {
    Poc::Poc(int fps): _r(std::make_shared<ecs::Registry>())
    {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RaylibPoc 3D");

        _camera = { 0 };
        _camera.position = (Vector3){ 0.0f, 5.0f, -10.0f };
        _camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
        _camera.fovy = 45.0f;
        _camera.projection = CAMERA_PERSPECTIVE;

        DisableCursor();
        SetTargetFPS(fps);
        _r->register_if_not_exist<ecs::component::Position3D>();
        _r->register_if_not_exist<ecs::component::Sprite>();
        _r->register_if_not_exist<ecs::component::Model>();
        _r->register_if_not_exist<ecs::component::Controllable>();
        _r->register_if_not_exist<ecs::component::KeyPressed>();
        _r->register_if_not_exist<ecs::component::Attributes>();
        _r->register_if_not_exist<ecs::component::Animations>();
        _r->register_if_not_exist<ecs::component::Gravitable>();
        _r->register_if_not_exist<ecs::component::Destroyable>();


        _r->_entities.addEntity(_cf.createEntity(_r, "poc_raylib/config/player.json"));
        _r->add_system(ecs::systems::ThirdDMouvementSystem("config/systems/basic_mouvement_system.json"));
        _r->add_system(ecs::systems::GravitableThirdDSystem());
    }

    Poc::~Poc() {
        CloseWindow();
    }

    std::size_t Poc::findPlayerIndex()
    {
        std::size_t i = 0;
        auto &attributes = _r->get_components<ecs::component::Attributes>();

        for (auto &&[attr]: ecs::custom_zip(attributes)) {
            if (!attr) {
                i += 1;
                continue;
            }

            if (attr->_entity_type == ecs::component::Attributes::EntityType::Player &&
                attr->_secondary_type == ecs::component::Attributes::SecondaryType::First) {
                    return i;
            }
            i += 1;
        }

        return i;
    }

    void Poc::draw()
    {
        auto &positions = _r->get_components<ecs::component::Position3D>();
        auto &sprites = _r->get_components<ecs::component::Sprite>();
        auto &models = _r->get_components<ecs::component::Model>();
        auto &attributes = _r->get_components<ecs::component::Attributes>();
        auto &rotates = _r->get_components<ecs::component::Rotate>();

        for (auto &&[pos, spri, mod, attr, rot] : ecs::custom_zip(positions, sprites, models, attributes, rotates)) {
            if (!pos || !spri || !mod || !rot) {
                continue;
            }

            Vector3 modelPos = {static_cast<float>(pos->_x), static_cast<float>(pos->_y), static_cast<float>(pos->_z)};
            Model model = LoadModel(mod->_pathToModel.c_str());
            Texture2D texture = LoadTexture(spri->_pathToSprite.c_str());

            if (texture.id == 0) {
                continue;
            }

            model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*rot->pitch, DEG2RAD*rot->yaw, DEG2RAD*rot->roll });

            SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);
            BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(_camera);

            DrawModelEx(model, modelPos, (Vector3){ 0.0f, 0.0f, 90.0f }, 0.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);
            DrawGrid(100, 1.0f);

            EndMode3D();
            EndDrawing();
            UnloadModel(model);
            UnloadTexture(texture);
        }
    }

    void Poc::handleMouvement()
    {
        auto &keys = _r->get_components<ecs::component::KeyPressed>();

        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            _camera.position.y -= 1;
        }

        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            _camera.position.y += 1;
        }

        if (IsKeyDown(KEY_W)) {
            keys[findPlayerIndex()]->_value = ecs::component::Key::Up;
        }

        if (IsKeyDown(KEY_A)) {
            keys[findPlayerIndex()]->_value = ecs::component::Key::Left;
        }

        if (IsKeyDown(KEY_S)) {
            keys[findPlayerIndex()]->_value = ecs::component::Key::Down;
        }

        if (IsKeyDown(KEY_D)) {
            keys[findPlayerIndex()]->_value = ecs::component::Key::Right;
        }

        if (IsKeyDown(KEY_SPACE)) {
            keys[findPlayerIndex()]->_value = ecs::component::Key::Jump;
        }

    }

    int Poc::run()
    {
        auto &keys = _r->get_components<ecs::component::KeyPressed>();

        while (!WindowShouldClose()) {
            UpdateCamera(&_camera, CAMERA_FIRST_PERSON);
            handleMouvement();
            draw();
            _r->run_systems(_cf, nullptr);
            keys[findPlayerIndex()]->_value = ecs::component::Key::NoneKey;
        }

        return EXIT_SUCCESS;
    }
}
