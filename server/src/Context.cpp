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
#include "Utils.hpp"

namespace rtype::server {
    Context::Context(std::shared_ptr<ecs::INetwork> network) : ecs::IContext(network) {}

    Context::~Context() {}

    void Context::destroyObject(int id)
    {
        if (!_network) {
            return;
        }
        auto arguments = ecs::utils::intToBytes(id);
        _network->broadcast(protocol::Packet(protocol::Operations::OBJECT_REMOVED, arguments));
    }

    void Context::createEnemy(int id)
    {
        if (!_network) {
            return;
        }
        auto arguments = ecs::utils::intToBytes(id);

        arguments.push_back(static_cast<uint8_t>(protocol::ObjectTypes::ENEMY));
        _network->broadcast(protocol::Packet(protocol::Operations::NEW_OBJECT, arguments));
    }

    void Context::animationObject(int id, const ecs::component::Animations &rect)
    {
        if (!_network) {
            return;
        }

        auto argument = ecs::utils::intToBytes(id);

        argument.push_back(static_cast<uint8_t>(rect._width >> 8));
        argument.push_back(static_cast<uint8_t>(rect._width & 0xFF));
        argument.push_back(static_cast<uint8_t>(rect._height >> 8));
        argument.push_back(static_cast<uint8_t>(rect._height & 0xFF));
        argument.push_back(static_cast<uint8_t>(rect._x >> 8));
        argument.push_back(static_cast<uint8_t>(rect._x & 0xFF));
        argument.push_back(static_cast<uint8_t>(rect._y >> 8));
        argument.push_back(static_cast<uint8_t>(rect._y & 0xFF));

        _network->broadcast(protocol::Packet(protocol::Operations::OBJECT_RECT, argument));
    }

    void Context::createBoss(int id)
    {
        if (!_network) {
            return;
        }
        auto arguments = ecs::utils::intToBytes(id);

        arguments.push_back(static_cast<uint8_t>(protocol::ObjectTypes::BOSS));
        _network->broadcast(protocol::Packet(protocol::Operations::NEW_OBJECT, arguments));
    }

    void Context::createBossProjectile(int id, const protocol::ObjectTypes &type)
    {
        if (!_network) {
            return;
        }
        auto arguments = ecs::utils::intToBytes(id);

        arguments.push_back(static_cast<uint8_t>(type));
        _network->broadcast(protocol::Packet(protocol::Operations::NEW_OBJECT, arguments));
    }

    void Context::createProjectile(int id, const protocol::ObjectTypes &type)
    {
        if (!_network) {
            return;
        }
        auto arguments = ecs::utils::intToBytes(id);

        arguments.push_back(static_cast<uint8_t>(type));
        _network->broadcast(protocol::Packet(protocol::Operations::NEW_OBJECT, arguments));
    }

    void Context::moveObject(int id, int x, int y)
    {
        if (!_network) {
            return;
        }
        auto arguments = ecs::utils::intToBytes(id);
        arguments.push_back(static_cast<uint8_t>(x >> 8));
        arguments.push_back(static_cast<uint8_t>(x & 0xFF));
        arguments.push_back(static_cast<uint8_t>(y >> 8));
        arguments.push_back(static_cast<uint8_t>(y & 0xFF));

        _network->broadcast(protocol::Packet(protocol::Operations::OBJECT_POSITION, arguments));
    }

    void Context::createMilespates(int id)
    {
        if (!_network) {
            return;
        }

        auto arguments = ecs::utils::intToBytes(id);

        arguments.push_back(static_cast<uint8_t>(protocol::ObjectTypes::MILESPATES));
        _network->broadcast(protocol::Packet(protocol::Operations::NEW_OBJECT, arguments));
    }
} // namespace rtype::server
