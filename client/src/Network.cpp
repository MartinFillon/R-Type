/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Network
*/

#include <iostream>
#include <memory>
#include <stdexcept>

#include "Network.hpp"
#include "ComponentFactory.hpp"
#include "Components/Animations.hpp"
#include "Components/Drawable.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "Entity.hpp"
#include "Packet.hpp"
#include "Protocol.hpp"
#include "Registry.hpp"

client::Network::Network(): _context(), _resolver(_context), _socket(_context)
{
    _updateRegistryFunctions[protocol::Operations::OBJECT_POSITION] =
    {[](std::shared_ptr<ecs::Registry> &r, const rtype::Packet &received_packet) {
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

    _updateRegistryFunctions[protocol::Operations::NEW_PLAYER] = 
    {[](std::shared_ptr<ecs::Registry> &r, const rtype::Packet &received_packet) {
        ecs::ComponentFactory factory(r, ecs::ComponentFactory::Mode::Client);
        switch (received_packet.getArguments()[1]) {
            case protocol::ObjectTypes::PLAYER_1:
                factory.createEntity("config/player1.json");
                break;
            case protocol::ObjectTypes::PLAYER_2:
                factory.createEntity("config/player2.json");
                break;
            case protocol::ObjectTypes::PLAYER_3:
                factory.createEntity("config/player3.json");
                break;
            case protocol::ObjectTypes::PLAYER_4:
                factory.createEntity("config/player4.json");
                break;
            default:
                break;
        }
    }};

    _updateRegistryFunctions[protocol::Operations::NEW_OBJECT] =
    {[](std::shared_ptr<ecs::Registry> &r, const rtype::Packet &received_packet) {
        ecs::ComponentFactory factory(r, ecs::ComponentFactory::Mode::Client);

        switch (received_packet.getArguments()[1]) {
            case protocol::ObjectTypes::ENEMY:
                factory.createEntity("config/ennemies.json");
                break;
            case protocol::ObjectTypes::MILESPATES:
                factory.createEntity("config/milespates.json");
                break;
            case protocol::ObjectTypes::BOSS:
                factory.createEntity("config/boss.json");
                break;
            default:
                break;        
        }
    }};

    _updateRegistryFunctions[protocol::Operations::OBJECT_REMOVED] =
    {[](std::shared_ptr<ecs::Registry> &r, const rtype::Packet &received_packet) {
        std::size_t id = received_packet.getArguments()[0];

        r->erase(id);
    }};

    _updateRegistryFunctions[protocol::Operations::PLAYER_CRASHED] =
    {[](std::shared_ptr<ecs::Registry> &r, const rtype::Packet &received_packet) {
        std::size_t id = received_packet.getArguments()[0];

        r->erase(id);
    }};

    _updateRegistryFunctions[protocol::Operations::PLAYER_LEFT] =
    {[](std::shared_ptr<ecs::Registry> &r, const rtype::Packet &received_packet) {
        std::size_t id = received_packet.getArguments()[0];

        r->erase(id);
    }};

}

void client::Network::setRegistry(std::shared_ptr<ecs::Registry> registry)
{
    _registry = registry;
}

int client::Network::setup(const std::string &host, const std::string &port)
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

void client::Network::updateRegistry(const rtype::Packet &received_packet)
{
    for (auto &[id, func]: _updateRegistryFunctions) {
        if (received_packet.getOpcode() == id) {
            func(_registry, received_packet);
        }
    }
}

int client::Network::run()
{
    bool running = true;

    std::thread context([&]() { _context.run(); });

    context.detach();

    send(rtype::Packet(protocol::Operations::READY));

    while (running) {

        Message message(DATA_MAX_SIZE);
        asio::error_code error;
        size_t len = _socket.receive_from(asio::buffer(message), _endpoint, 0, error);

        rtype::Packet received_packet(message);

        if (!error && len) {
            //std::cout << "Packet recu du server! OptCode: " << std::to_string(received_packet.getOpcode()) << std::endl;
        }

        updateRegistry(received_packet);

        if (_keepaliveClock.getSeconds() > KEEPALIVE_TIMEOUT) {
            send(protocol::Operations::PING, {});
            _keepaliveClock.restart();
        }
    }

    return EXIT_SUCCESS;
}

void client::Network::send(const rtype::Packet &packet)
{
    if (!packet.isValid()) {
        std::cerr << "Packet is not valid" << std::endl;
        return;
    }

    _socket.send_to(asio::buffer(packet.toMessage()), _endpoint);
}

void client::Network::send(const uint8_t opcode, const Arguments &arguments)
{
    rtype::Packet packet(opcode, arguments);

    send(packet);
}
