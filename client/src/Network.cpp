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
#include <stdexcept>

#include "ComponentFactory.hpp"
#include "Components/Destroyable.hpp"
#include "Network.hpp"
#include "Packet.hpp"
#include "Protocol.hpp"
#include "Registry.hpp"

namespace rtype::client {

    Network::Network() : _context(), _resolver(_context), _socket(_context)
    {
        _updateRegistryFunctions[protocol::Operations::WELCOME] = {[](std::shared_ptr<ecs::Registry> &r,
                                                                      const protocol::Packet &received_packet) {}};

        _updateRegistryFunctions[protocol::Operations::OBJECT_POSITION] = {[](std::shared_ptr<ecs::Registry> &r,
                                                                              const protocol::Packet &received_packet) {
            std::size_t id = received_packet.getArguments()[0];
            auto &pos = r->get_components<ecs::component::Position>();

            if (id > pos.size()) {
                return;
            }

            int x = (received_packet.getArguments()[1] << 8) + (received_packet.getArguments()[2]);
            int y = (received_packet.getArguments()[3] << 8) + (received_packet.getArguments()[4]);

            pos[id]->_x = x;
            pos[id]->_y = y;
        }};

        _updateRegistryFunctions[protocol::Operations::NEW_PLAYER] = {[](std::shared_ptr<ecs::Registry> &r,
                                                                         const protocol::Packet &received_packet) {
            ecs::ComponentFactory factory(r, ecs::ComponentFactory::Mode::Client);

            int id = received_packet.getArguments()[0];
            int type = received_packet.getArguments()[1];

            std::cerr << "New player " << id << " type " << type << std::endl;
            switch (type) {
                case protocol::ObjectTypes::PLAYER_1:
                    factory.createEntity(id, "config/player0.json");
                    break;
                case protocol::ObjectTypes::PLAYER_2:
                    factory.createEntity(id, "config/player1.json");
                    break;
                case protocol::ObjectTypes::PLAYER_3:
                    factory.createEntity(id, "config/player2.json");
                    break;
                case protocol::ObjectTypes::PLAYER_4:
                    factory.createEntity(id, "config/player3.json");
                    break;
                default:
                    break;
            }
        }};

        _updateRegistryFunctions[protocol::Operations::NEW_OBJECT] = {[](std::shared_ptr<ecs::Registry> &r,
                                                                         const protocol::Packet &received_packet) {
            ecs::ComponentFactory factory(r, ecs::ComponentFactory::Mode::Client);

            uint8_t id = received_packet.getArguments()[0];
            uint8_t type = received_packet.getArguments()[1];

            switch (type) {
                case protocol::ObjectTypes::ENEMY:
                    factory.createEntity(id, "config/ennemies.json");
                    break;
                case protocol::ObjectTypes::MILESPATES:
                    factory.createEntity(id, "config/milespates.json");
                    break;
                case protocol::ObjectTypes::BOSS:
                    factory.createEntity(id, "config/boss.json");
                    break;
                case protocol::ObjectTypes::BULLET:
                    factory.createEntity(id, "config/projectile.json");
                    break;
                default:
                    break;
            }
        }};

        _updateRegistryFunctions[protocol::Operations::OBJECT_REMOVED] = {[](std::shared_ptr<ecs::Registry> &r,
                                                                             const protocol::Packet &received_packet) {
            std::size_t id = received_packet.getArguments()[0];

            auto &destroyable = r->register_if_not_exist<ecs::component::Destroyable>();
            auto &animations = r->register_if_not_exist<ecs::component::Animations>();

            if (animations[id]->_object == ecs::component::Object::Weapon) {
                r->erase(id);
            } else {
                destroyable[id]->_destroyable = true;
                animations[id]->_object = ecs::component::Object::InDestroy;
            }
        }};

        _updateRegistryFunctions[protocol::Operations::PLAYER_CRASHED] = {[](std::shared_ptr<ecs::Registry> &r,
                                                                             const protocol::Packet &received_packet) {
            std::size_t id = received_packet.getArguments()[0];

            r->erase(id);
        }};

        _updateRegistryFunctions[protocol::Operations::PLAYER_LEFT] = {[](std::shared_ptr<ecs::Registry> &r,
                                                                          const protocol::Packet &received_packet) {
            std::size_t id = received_packet.getArguments()[0];

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

        } catch (const std::runtime_error &e) {

            std::cerr << e.what() << std::endl;
            return ERROR;

        } catch (const std::exception &e) {

            std::cerr << e.what() << std::endl;
            return ERROR;
        }

        return SUCCESS;
    }

    void Network::updateRegistry(const protocol::Packet &received_packet)
    {
        for (auto &[id, func] : _updateRegistryFunctions) {
            if (received_packet.getOpcode() == id) {
                func(_registry, received_packet);
            }
        }
    }

    int Network::run()
    {
        bool running = true;

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
                std::cerr << "Server full\n";
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
