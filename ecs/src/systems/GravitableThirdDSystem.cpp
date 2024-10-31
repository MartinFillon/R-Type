/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GravitableThirdDSystem
*/

#include "Systems/GravitableThirdDSystem.hpp"
#include "Components/Attributes.hpp"
#include "Components/Gravitable.hpp"
#include "Components/KeyPressed.hpp"
#include "Components/Position3D.hpp"
#include "Components/RectangleShape.hpp"
#include "ZipperIterator.hpp"

int ecs::systems::GravitableThirdDSystem::findInitialY(std::shared_ptr<Registry> &r)
{
    auto &rectangles = r->get_components<ecs::component::RectangleShape>();
    auto &positions = r->get_components<ecs::component::Position3D>();
    auto &pos = r->get_components<ecs::component::Position3D>();
    auto &attributes = r->get_components<ecs::component::Attributes>();
    int initialY = INITIAL_Y;
    bool onPlatform = false;
    size_t j = 0;

    for (; j < pos.size(); ++j) {
        if (!pos[j] || !attributes[j]) {
            continue;
        }
        if (attributes[j]->_entity_type == ecs::component::Attributes::EntityType::Player) {
            continue;
        }
    }

    for (size_t i = 0; i < positions.size(); ++i) {
        if (!rectangles[i] || !attributes[i]) {
            continue;
        }
        float rectMinX = positions[i]->_x - rectangles[i]->_length / 2.0f;
        float rectMaxX = positions[i]->_x + rectangles[i]->_length / 2.0f;
        float rectMinZ = positions[i]->_z - rectangles[i]->_width / 2.0f;
        float rectMaxZ = positions[i]->_z + rectangles[i]->_width / 2.0f;
        if ((pos[j]->_x < rectMaxX && pos[j]->_x > rectMinX) &&
            (pos[j]->_z < rectMaxZ && pos[j]->_z > rectMinZ)) {
                onPlatform = true;
        }
        if (onPlatform) {
            initialY = positions[i]->_y + MAX_Y;
        }
    }

    return initialY;
}

void ecs::systems::GravitableThirdDSystem::operator()(
    std::shared_ptr<Registry> &r,
    std::shared_ptr<IContext> ctx,
    ComponentFactory &factory
)
{
    auto &positions = r->get_components<ecs::component::Position3D>();
    auto &gravitables = r->get_components<ecs::component::Gravitable>();
    auto &keys = r->get_components<ecs::component::KeyPressed>();
    auto &attributes = r->get_components<ecs::component::Attributes>();

    int initialY = findInitialY(r);
    int targetY = MAX_Y + initialY;

    bool onPlatform = false;

    for (auto &&[pos, gravit, key, attr] : custom_zip(positions, gravitables, keys, attributes)) {

            if (attr->_entity_type != ecs::component::Attributes::EntityType::Player) {
                initialY = 0;
            }

        if (key->_value == ecs::component::Key::Jump && !gravit->_isJumping && !gravit->_isFalling) {
            gravit->_isJumping = true;
        }

        if (gravit->_isJumping && pos->_y < targetY) {
            pos->_y += gravit->_gravityFall;
        }

        if ((gravit->_isJumping && pos->_y >= targetY) || (pos->_y > initialY && !gravit->_isJumping && !gravit->_isFalling)) {
            gravit->_isJumping = false;
            gravit->_isFalling = true;
        }

        if (gravit->_isFalling) {

            if (pos->_y > initialY) {
                pos->_y -= gravit->_gravityFall;
            }

            if (attr->_entity_type != ecs::component::Attributes::EntityType::Player) {
                continue;
            }

            auto &rectangles = r->get_components<ecs::component::RectangleShape>();

            for (size_t i = 0; i < positions.size(); ++i) {
                if (!rectangles[i] || !attributes[i]) {
                    continue;
                }

                float rectMinX = positions[i]->_x - rectangles[i]->_length / 2.0f;
                float rectMaxX = positions[i]->_x + rectangles[i]->_length / 2.0f;
                float rectMinZ = positions[i]->_z - rectangles[i]->_width / 2.0f;
                float rectMaxZ = positions[i]->_z + rectangles[i]->_width / 2.0f;

                if ((pos->_x < rectMaxX && pos->_x > rectMinX) &&
                    (pos->_z < rectMaxZ && pos->_z > rectMinZ)) {
                        onPlatform = true;
                }

                if (onPlatform) {
                    initialY = positions[i]->_y + 3;
                }
            }

            if (!onPlatform && pos->_y > initialY) {
                pos->_y -= gravit->_gravityFall;
            }
        }

        if (gravit->_isFalling && pos->_y <= initialY) {
            pos->_y = initialY;
            gravit->_isJumping = false;
            gravit->_isFalling = false;
            key->_value = ecs::component::Key::NoneKey;
        }
    }
}
