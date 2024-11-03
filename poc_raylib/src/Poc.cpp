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
#include "Components/Animations3D.hpp"
#include "Components/Attributes.hpp"
#include "Components/Color.hpp"
#include "Components/Controllable.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Gravitable.hpp"
#include "Components/KeyPressed.hpp"
#include "Components/Model.hpp"
#include "Components/Planes.hpp"
#include "Components/Position3D.hpp"
#include "Components/RectangleShape.hpp"
#include "Components/Rotate.hpp"
#include "Components/Sprite.hpp"
#include "Registry.hpp"
#include "Systems/ColisionThirdDimension.hpp"
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
        _r->register_if_not_exist<ecs::component::Rotate>();
        _r->register_if_not_exist<ecs::component::RectangleShape>();
        _r->register_if_not_exist<ecs::component::Color>();
        _r->register_if_not_exist<ecs::component::Animations3D>();

        try {
            _r->_entities.addEntity(_cf.createEntity(_r, "poc_raylib/config/player.json"));
            _r->_entities.addEntity(_cf.createEntity(_r, "poc_raylib/config/platform.json"));
            _r->_entities.addEntity(_cf.createEntity(_r, "poc_raylib/config/secondPlatform.json"));
            _r->_entities.addEntity(_cf.createEntity(_r, "poc_raylib/config/thirdPlatform.json"));
            _r->_entities.addEntity(_cf.createEntity(_r, "poc_raylib/config/fourthPlatform.json"));
            _r->_entities.addEntity(_cf.createEntity(_r, "poc_raylib/config/fivePlatform.json"));
            _r->_entities.addEntity(_cf.createEntity(_r, "poc_raylib/config/plane.json"));
            _r->_entities.addEntity(_cf.createEntity(_r, "poc_raylib/config/finishPlatform.json"));
        } catch (const ecs::ComponentFactory::ComponentNotCreated &e) {
            std::cerr << e.what() << std::endl;
        }
        _r->add_system<ecs::systems::ThirdDMouvementSystem>();
        _r->add_system<ecs::systems::GravitableThirdDSystem>();
        _r->add_system<ecs::systems::ColisionThirdDimension>();
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

    int Poc::drawShapes()
    {
        auto &positions = _r->get_components<ecs::component::Position3D>();
        auto &rectangles = _r->get_components<ecs::component::RectangleShape>();
        auto &colors = _r->get_components<ecs::component::Color>();
        auto &attributes = _r->get_components<ecs::component::Attributes>();

        for (auto &&[pos, rect, color, attr] : ecs::custom_zip(positions, rectangles, colors, attributes)) {
            if (attr->_entity_type == ecs::component::Attributes::EntityType::Rectangle) {
                Vector3 modelPos = {static_cast<float>(pos->_x), static_cast<float>(pos->_y), static_cast<float>(pos->_z)};
                DrawCube(modelPos, rect->_width, rect->_height, rect->_length, Color{color->_r, color->_g, color->_b, color->_a});
                DrawCubeWires(modelPos, rect->_width, rect->_height, rect->_length, MAROON);
            }
        }

        auto &planes = _r->get_components<ecs::component::Planes>();
        for (auto &&[pos, color, attr, plane] : ecs::custom_zip(positions, colors, attributes, planes)) {
            if (attr->_entity_type == ecs::component::Attributes::EntityType::Planes) {
                Vector3 modelPos = {static_cast<float>(pos->_x), static_cast<float>(pos->_y), static_cast<float>(pos->_z)};
                DrawPlane(modelPos, Vector2{(float)plane->_width, (float)plane->_lenght}, Color{color->_r, color->_g, color->_b, color->_a});
            }
        }

        return EXIT_SUCCESS;
    }

    int Poc::draw()
    {
        auto &attributes = _r->get_components<ecs::component::Attributes>();
        auto &positions = _r->get_components<ecs::component::Position3D>();
        auto &animations = _r->get_components<ecs::component::Animations3D>();
        auto &rotates = _r->get_components<ecs::component::Rotate>();
        auto &sprites = _r->get_components<ecs::component::Sprite>();
        auto &models = _r->get_components<ecs::component::Model>();

        for (auto &&[pos, spri, mod, attr, rot, anim]:
            ecs::custom_zip(positions, sprites, models, attributes, rotates, animations)) {
            if (!pos || !spri || !mod || !rot || !anim) {
                continue;
            }
            if (attr->_entity_type == ecs::component::Attributes::EntityType::Rectangle ||
                attr->_entity_type == ecs::component::Attributes::EntityType::Planes) {
                continue;
            }
            Vector3 modelPos = {static_cast<float>(pos->_x), static_cast<float>(pos->_y - 1), static_cast<float>(pos->_z)};
            Model model = LoadModel(mod->_pathToModel.c_str());
            Texture2D texture = LoadTexture(spri->_pathToSprite.c_str());

            if (anim->_state) {
                ModelAnimation *anims = LoadModelAnimations("poc_raylib/assets/Animation/Jump.glb", &anim->_animCount);
                anim->_animFrameCounter += 5;
                UpdateModelAnimation(model, anims[0], anim->_animFrameCounter);
                if (anim->_animFrameCounter >= anims[0].frameCount) {
                    anim->_animFrameCounter = 0;
                    anim->_state = false;
                }
            }

            if (texture.id == 0) {
                continue;
            }

            model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*rot->_pitch, DEG2RAD*rot->_yaw, DEG2RAD*rot->_roll });

            SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);
            DrawModelEx(model, modelPos, (Vector3){ 0.0f, 90.0f, 0.0f }, 0.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);
            DrawGrid(100, 1.0f);

            UnloadModel(model);
            UnloadTexture(texture);
        }

        return EXIT_SUCCESS;
    }

    int Poc::handleMouvement()
    {
        auto &keys = _r->get_components<ecs::component::KeyPressed>();
        auto &rotation = _r->get_components<ecs::component::Rotate>();
        auto &animation = _r->get_components<ecs::component::Animations3D>();
        std::size_t playerIndex = findPlayerIndex();

        if (IsKeyDown(KEY_W)) {
            keys[playerIndex]->_value = ecs::component::Key::Up;
            if (rotation[playerIndex]->_yaw < ROTATION_FRONT) {
                rotation[playerIndex]->_yaw += ROTATION_PADDING;
                return EXIT_FAILURE;
            } else if (rotation[playerIndex]->_yaw > ROTATION_FRONT) {
                rotation[playerIndex]->_yaw -= ROTATION_PADDING;
                return EXIT_FAILURE;
            }
            if (rotation[playerIndex]->_yaw == ROTATION_FRONT) {
                return EXIT_SUCCESS;
            }
        }

        if (IsKeyDown(KEY_A)) {
            keys[playerIndex]->_value = ecs::component::Key::Left;
            if (rotation[playerIndex]->_yaw != ROTATION_RIGHT) {
                rotation[playerIndex]->_yaw += ROTATION_PADDING;
                return EXIT_FAILURE;
            } else if (rotation[playerIndex]->_yaw == ROTATION_RIGHT) {
                return EXIT_SUCCESS;
            }
        }

        if (IsKeyDown(KEY_S)) {
            keys[playerIndex]->_value = ecs::component::Key::Down;
            if (rotation[playerIndex]->_yaw > ROTATION_BACK) {
                rotation[playerIndex]->_yaw -= ROTATION_PADDING;
                return EXIT_FAILURE;
            } else if (rotation[playerIndex]->_yaw == ROTATION_BACK) {
                return EXIT_SUCCESS;
            }
        }

        if (IsKeyDown(KEY_D)) {
            keys[playerIndex]->_value = ecs::component::Key::Right;
            if (rotation[playerIndex]->_yaw != ROTATION_LEFT) {
                rotation[playerIndex]->_yaw -= ROTATION_PADDING;
                return EXIT_FAILURE;
            } else if (rotation[playerIndex]->_yaw == ROTATION_LEFT) {
                return EXIT_SUCCESS;
            }
        }

        if (IsKeyDown(KEY_SPACE)) {
            keys[playerIndex]->_value = ecs::component::Key::Jump;
        }

        if (IsKeyDown(KEY_F)) {
            animation[playerIndex]->_state = !animation[playerIndex]->_state;
        }

        return EXIT_SUCCESS;
    }

    int Poc::run()
    {
        auto &keys = _r->get_components<ecs::component::KeyPressed>();

        while (!WindowShouldClose()) {
            auto &positions = _r->get_components<ecs::component::Position3D>();
            auto &rotates = _r->get_components<ecs::component::Rotate>();
            std::size_t playerIndex = findPlayerIndex();

            if (playerIndex < positions.size() && positions[playerIndex] && playerIndex < rotates.size() && rotates[playerIndex]) {
                float cameraDistance = 10.0f;
                float cameraHeight = 6.0f;

                Vector3 playerPosition = {
                    static_cast<float>(positions[playerIndex]->_x),
                    static_cast<float>(positions[playerIndex]->_y),
                    static_cast<float>(positions[playerIndex]->_z)
                };

                float yaw = DEG2RAD * rotates[playerIndex]->_yaw;
                _camera.position = {
                    playerPosition.x - cameraDistance * sin(yaw),
                    playerPosition.y + cameraHeight,
                    playerPosition.z - cameraDistance * cos(yaw)
                };

                _camera.target = playerPosition;
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(_camera);

            drawShapes();
            draw();

            EndMode3D();
            EndDrawing();

            if (!handleMouvement()) {
                _r->run_systems(_cf, nullptr);
            }
            keys[findPlayerIndex()]->_value = ecs::component::Key::NoneKey;
        }

        return EXIT_SUCCESS;
    }

}
