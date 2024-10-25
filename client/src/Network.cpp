/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Network
*/

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <spdlog/spdlog.h>
#include <stdexcept>

#include "Clock.hpp"
#include "ComponentFactory.hpp"
#include "Components/Attributes.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Position.hpp"
#include "Network.hpp"
#include "Packet.hpp"
#include "Protocol.hpp"
#include "Registry.hpp"
#include "Utils.hpp"

namespace rtype::client {

    Network::Network() : _context(), _resolver(_context), _socket(_context)
    {
        _updateRegistryFunctions[protocol::Operations::WELCOME] = {[](std::shared_ptr<ecs::Registry> &r,
                                                                      const protocol::Packet &received_packet,
                                                                      std::shared_ptr<ecs::ComponentFactory> &_cf) {}};

        _updateRegistryFunctions[protocol::Operations::OBJECT_POSITION] = {
            [](std::shared_ptr<ecs::Registry> &r,
               const protocol::Packet &received_packet,
               std::shared_ptr<ecs::ComponentFactory> &_cf) {
                auto arguments = received_packet.getArguments();
                int id = ecs::utils::bytesToInt(arguments);
                auto &pos = r->register_if_not_exist<ecs::component::Position>();

                if (id > pos.size()) {
                    return;
                }

                int x = (arguments[4] << 8) + (arguments[5]);
                int y = (arguments[6] << 8) + (arguments[7]);

                pos[id]->_x = x;
                pos[id]->_y = y;
            }
        };

        _updateRegistryFunctions[protocol::Operations::OBJECT_RECT] = {[](std::shared_ptr<ecs::Registry> &r,
                                                                          const protocol::Packet &received_packet,
                                                                          std::shared_ptr<ecs::ComponentFactory> &_cf) {
            auto arguments = received_packet.getArguments();
            int id = ecs::utils::bytesToInt(arguments);
            int width = (received_packet.getArguments()[4] << 8) + (received_packet.getArguments()[5]);
            int height = (received_packet.getArguments()[6] << 8) + (received_packet.getArguments()[7]);
            int x = (received_packet.getArguments()[8] << 8) + (received_packet.getArguments()[9]);
            int y = (received_packet.getArguments()[10] << 8) + (received_packet.getArguments()[11]);
            auto &anim = r->register_if_not_exist<ecs::component::Animations>();

            anim[id] = ecs::component::Animations{ecs::Clock(), width, height, x, y};
        }};

        _updateRegistryFunctions[protocol::Operations::NEW_PLAYER] = {
            [](std::shared_ptr<ecs::Registry> &r,
               const protocol::Packet &received_packet,
               std::shared_ptr<ecs::ComponentFactory> &_cf) {
                auto arguments = received_packet.getArguments();
                int id = ecs::utils::bytesToInt(arguments);
                int type = arguments[4];

                switch (type) {
                    case protocol::ObjectTypes::PLAYER_1:
                        _cf->createEntity(r, id, CONFIG_PLAYER_0);
                        break;
                    case protocol::ObjectTypes::PLAYER_2:
                        _cf->createEntity(r, id, CONFIG_PLAYER_1);
                        break;
                    case protocol::ObjectTypes::PLAYER_3:
                        _cf->createEntity(r, id, CONFIG_PLAYER_2);
                        break;
                    case protocol::ObjectTypes::PLAYER_4:
                        _cf->createEntity(r, id, CONFIG_PLAYER_3);
                        break;
                    default:
                        break;
                }
            },
        };

        _updateRegistryFunctions[protocol::Operations::NEW_OBJECT] = {[](std::shared_ptr<ecs::Registry> &r,
                                                                         const protocol::Packet &received_packet,
                                                                         std::shared_ptr<ecs::ComponentFactory> &_cf) {
            auto arguments = received_packet.getArguments();
            int id = ecs::utils::bytesToInt(arguments);
            int type = arguments[4];

            switch (type) {
                case protocol::ObjectTypes::ENEMY:
                    _cf->createEntity(r, id, CONFIG_ENNEMIES);
                    break;
                case protocol::ObjectTypes::MILESPATES:
                    _cf->createEntity(r, id, CONFIG_MILEPATES);
                    break;
                case protocol::ObjectTypes::BOSS:
                    _cf->createEntity(r, id, CONFIG_BOSS);
                    break;
                case protocol::ObjectTypes::BULLET:
                    _cf->createEntity(r, id, CONFIG_PROJECTILE);
                    break;
                case protocol::ObjectTypes::PLAYER_BULLET:
                    _cf->createEntity(r, id, CONFIG_PLAYER_PROJECTILE);
                    break;
                default:
                    break;
            }
        }};

        _updateRegistryFunctions[protocol::Operations::OBJECT_REMOVED] = {[](std::shared_ptr<ecs::Registry> &r,
                                                                             const protocol::Packet &received_packet,
                                                                             std::shared_ptr<ecs::ComponentFactory> &_cf
                                                                          ) {
            auto arguments = received_packet.getArguments();
            int id = ecs::utils::bytesToInt(arguments);

            auto &destroyable = r->register_if_not_exist<ecs::component::Destroyable>();

            if (destroyable[id])
                destroyable[id]->_state = ecs::component::Destroyable::DestroyState::WAITING;
        }};

        _updateRegistryFunctions[protocol::Operations::PLAYER_CRASHED] = {[](std::shared_ptr<ecs::Registry> &r,
                                                                             const protocol::Packet &received_packet,
                                                                             std::shared_ptr<ecs::ComponentFactory> &_cf
                                                                          ) {
            auto arguments = received_packet.getArguments();
            int id = ecs::utils::bytesToInt(arguments);

            auto &destroyable = r->register_if_not_exist<ecs::component::Destroyable>();

            if (destroyable[id])
                destroyable[id]->_state = ecs::component::Destroyable::DestroyState::WAITING;
        }};

        _updateRegistryFunctions[protocol::Operations::PLAYER_LEFT] = {[](std::shared_ptr<ecs::Registry> &r,
                                                                          const protocol::Packet &received_packet,
                                                                          std::shared_ptr<ecs::ComponentFactory> &_cf) {
            auto arguments = received_packet.getArguments();
            int id = ecs::utils::bytesToInt(arguments);

            r->erase(id);
        }};
    }

    void Network::setRegistry(std::shared_ptr<ecs::Registry> registry)
    {
        _registry = registry;
    }

    int Network::setup(const std::string &host, const std::string &port)
    {
        try {

            _endpoint = *_resolver.resolve(UDP::v4(), host, port).begin();
            _socket.open(UDP::v4());
            _socket.non_blocking(true);

        } catch (const std::exception &e) {
            spdlog::error("{}", e.what());
            return ERROR;
        }

        return SUCCESS;
    }

    void Network::updateRegistry(const protocol::Packet &received_packet)
    {
        for (auto &[id, func] : _updateRegistryFunctions) {
            if (received_packet.getOpcode() == id) {
                func(_registry, received_packet, _cf);
            }
        }
    }

    void Network::stop()
    {
        running = false;
    }

    int Network::run()
    {
        std::thread context([&]() { _context.run(); });

        context.detach();

        send(protocol::Packet(protocol::Operations::READY));

        while (running) {

            Message message(DATA_MAX_SIZE);
            asio::error_code error;
            size_t len = _socket.receive_from(asio::buffer(message), _endpoint, 0, error);

            protocol::Packet packet(message);

            if (!packet.isValid()) {
                continue;
            }

            if (packet.getOpcode() == protocol::Operations::REFUSED) {
                spdlog::error("Server full");
                return EXIT_FAILURE;
            }

            updateRegistry(protocol::Packet(message));

            if (_keepaliveClock.getSeconds() > KEEPALIVE_TIMEOUT) {
                send(protocol::Operations::PING, {});
                _keepaliveClock.restart();
            }
        }

        return EXIT_SUCCESS;
    }

    void Network::send(const protocol::Packet &packet)
    {
        if (!packet.isValid()) {
            return;
        }

        _socket.send_to(asio::buffer(packet.toMessage()), _endpoint);
    }

    void Network::send(const uint8_t opcode, const Arguments &arguments)
    {
        protocol::Packet packet(opcode, arguments);

        send(packet);
    }
} // namespace rtype::client
