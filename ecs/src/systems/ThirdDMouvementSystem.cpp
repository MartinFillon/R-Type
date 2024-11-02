/*
** EPITECH PROJECT 2024
** R-Type
** File description:
** ThirdDMouvementSystem
*/

#include "Systems/ThirdDMouvementSystem.hpp"
#include "ComponentFactory.hpp"
#include "Components/Attributes.hpp"
#include "Components/Controllable.hpp"
#include "Components/KeyPressed.hpp"
#include "Components/Position3D.hpp"
#include "Components/RectangleShape.hpp"
#include "IContext.hpp"
#include "Systems/ISystems.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

ecs::systems::ThirdDMouvementSystem::ThirdDMouvementSystem(const nlohmann::json &config) {}

bool ecs::systems::ThirdDMouvementSystem::checkCollision(std::shared_ptr<Registry> &r, ecs::component::Position3D &pos, ecs::component::Position3D previousPos) {
    auto &attributes = r->get_components<ecs::component::Attributes>();
    auto &rectanglePositions = r->get_components<ecs::component::Position3D>();
    auto &rectangleShapes = r->get_components<ecs::component::RectangleShape>();

    for (size_t i = 0; i < rectanglePositions.size(); ++i) {
        if (attributes[i]->_entity_type == ecs::component::Attributes::EntityType::Rectangle) {
            float rectMinX = rectanglePositions[i]->_x - rectangleShapes[i]->_length / 2.0f;
            float rectMaxX = rectanglePositions[i]->_x + rectangleShapes[i]->_length / 2.0f;
            float rectMinZ = rectanglePositions[i]->_z - rectangleShapes[i]->_width / 2.0f;
            float rectMaxZ = rectanglePositions[i]->_z + rectangleShapes[i]->_width / 2.0f;

            if ((pos._x < rectMaxX && pos._x > rectMinX) &&
                (pos._z < rectMaxZ && pos._z > rectMinZ) &&
                (pos._z < rectMaxZ && pos._z > rectMinZ) &&
                pos._y < rectanglePositions[i]->_y + rectangleShapes[i]->_height) {
                return true;
            }
        }
    }

    return false;
}

void ecs::systems::ThirdDMouvementSystem::operator()(
    std::shared_ptr<Registry> &r,
    std::shared_ptr<IContext> ctx,
    ComponentFactory &factory
)
{
    auto &positions = r->get_components<ecs::component::Position3D>();
    auto &keys = r->get_components<ecs::component::KeyPressed>();
    auto &controllables = r->get_components<ecs::component::Controllable>();

    for (auto &&[pos, key, ctrl] : custom_zip(positions, keys, controllables)) {

        if (!pos || !key || !ctrl) {
            continue;
        }
        if (!ctrl->_controllable) {
            continue;
        }

        ecs::component::Position3D previousPos = *pos;

        if (key->_value == ecs::component::Key::Left) {
            pos->_x += ctrl->_speed;
        }
        if (key->_value == ecs::component::Key::Right) {
            pos->_x -= ctrl->_speed;
        }
        if (key->_value == ecs::component::Key::Up) {
            pos->_z += ctrl->_speed;
        }
        if (key->_value == ecs::component::Key::Down) {
            pos->_z -= ctrl->_speed;
        }

        if (checkCollision(r, *pos, previousPos)) {
            *pos = previousPos;
        }
    }
}
