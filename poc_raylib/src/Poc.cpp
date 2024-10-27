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
#include "Components/Attributes.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Gravitable.hpp"
#include "Components/KeyPressed.hpp"
#include "Components/Model.hpp"
#include "Components/Position3D.hpp"
#include "Components/Sprite.hpp"
#include "Registry.hpp"
#include "Systems/ThirdDMouvementSystem.hpp"
#include "ZipperIterator.hpp"

namespace poc {
    Poc::Poc(int fps): _r(std::make_shared<ecs::Registry>())
    {
        std::cerr << "Go window\n";
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RaylibPoc 3D");

        _camera = { 0 };
        _camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
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
    }

    Poc::~Poc() {
        CloseWindow();
    }

    void Poc::draw()
    {
        auto &positions = _r->get_components<ecs::component::Position3D>();
        auto &sprites = _r->get_components<ecs::component::Sprite>();
        auto &models = _r->get_components<ecs::component::Model>();

        for (auto &&[pos, spri, mod] : ecs::custom_zip(positions, sprites, models)) {
            if (!pos || !spri || !mod) {
                continue;
            }

            Vector3 modelPos = {static_cast<float>(pos->_x), static_cast<float>(pos->_y), static_cast<float>(pos->_z)};
            Model model = LoadModel(mod->_pathToModel.c_str());
            Texture2D texture = LoadTexture(spri->_pathToSprite.c_str());

            if (texture.id == 0) {
                continue;
            }

            SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);
            BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(_camera);

            DrawModelEx(model, modelPos, (Vector3){ 1.0f, 0.0f, 0.0f }, 0.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);
            DrawGrid(10, 1.0f);

            EndMode3D();
            EndDrawing();
            UnloadModel(model);
            UnloadTexture(texture);
        }
    }

    void Poc::handleMouvement()
    {
        auto &attributes = _r->get_components<ecs::component::Attributes>();
        auto &keys = _r->get_components<ecs::component::KeyPressed>();

        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            _camera.position.y -= 1;
        }

        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            _camera.position.y += 1;
        }

        for (auto &&[attr, key]: ecs::custom_zip(attributes, keys)) {
            if (!attr || !key) {
                continue;
            }

            if (attr->_entity_type != ecs::component::Attributes::EntityType::Player) {
                continue;
            }

            if (IsKeyDown(KEY_Z)) {
                key->_value = ecs::component::Key::Up;
            }

            if (IsKeyDown(KEY_Q)) {
                key->_value = ecs::component::Key::Left;
            }

            if (IsKeyDown(KEY_S)) {
                key->_value = ecs::component::Key::Down;
            }

            if (IsKeyDown(KEY_D)) {
                key->_value = ecs::component::Key::Right;
            }

            if (IsKeyDown(KEY_SPACE)) {
                key->_value = ecs::component::Key::Jump;
            }
        }


    }

    int Poc::run()
    {
        while (!WindowShouldClose()) {
            UpdateCamera(&_camera, CAMERA_FIRST_PERSON);
            draw();
            _r->run_systems(_cf, nullptr);
        }

        return EXIT_SUCCESS;
    }
}
