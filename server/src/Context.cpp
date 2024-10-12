/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Context
*/

#include "Context.hpp"
#include <cstdint>
#include "Packet.hpp"
#include "Protocol.hpp"

namespace rtype::server {
    Context::Context(std::shared_ptr<ecs::INetwork> network) : ecs::IContext(network) {}

    void Context::destroyObject(int id)
    {
        if (!_network) {
            return;
        }
        _network->broadcast(protocol::Packet(protocol::Operations::OBJECT_REMOVED, {static_cast<uint8_t>(id)}));
    }

    void Context::createEnemy(int id)
    {
        if (!_network) {
            return;
        }
        _network->broadcast(protocol::Packet(
            protocol::Operations::NEW_OBJECT,
            {static_cast<uint8_t>(id), static_cast<uint8_t>(protocol::ObjectTypes::ENEMY)}
        ));
    }

    void Context::animationObject(int id, const ecs::component::Animations &rect)
    {
        if (!_network) {
            return;
        }

        _network->broadcast(protocol::Packet(
            protocol::Operations::OBJECT_RECT,
            {static_cast<uint8_t>(id),
            static_cast<uint8_t>(rect._width >> 8),
            static_cast<uint8_t>(rect._width & 0xFF),
            static_cast<uint8_t>(rect._height >> 8),
            static_cast<uint8_t>(rect._height & 0xFF),
            static_cast<uint8_t>(rect._x >> 8),
            static_cast<uint8_t>(rect._x & 0xFF),
            static_cast<uint8_t>(rect._y >> 8),
            static_cast<uint8_t>(rect._y & 0xFF)}
        ));
    }

    void Context::createProjectile(int id, const protocol::ObjectTypes &type)
    {
        if (!_network) {
            return;
        }
        _network->broadcast(protocol::Packet(
            protocol::Operations::NEW_OBJECT,
            {static_cast<uint8_t>(id), static_cast<uint8_t>(type)}
        ));
    }

    void Context::moveObject(int id, int x, int y)
    {
        if (!_network) {
            return;
        }
        _network->broadcast(protocol::Packet(
            protocol::Operations::OBJECT_POSITION,
            {static_cast<uint8_t>(id),
             static_cast<uint8_t>(x >> 8),
             static_cast<uint8_t>(x & 0xFF),
             static_cast<uint8_t>(y >> 8),
             static_cast<uint8_t>(y & 0xFF)}
        ));
    }
} // namespace rtype::server
