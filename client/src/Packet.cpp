/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Packet
*/

#include "Packet.hpp"

#include "protocol.hpp"

rtype::Packet::Packet(const Message &message) : _isValid(false), _opcode(-1), _arguments({})
{
    if (message.size() < MESSAGE_MIN_SIZE) {
        return;
    }

    _magicNumber = GET_MAGIC_NUMBER(message);

    if (_magicNumber != protocol::MAGIC) {
        return;
    }

    _opcode = message[MESSAGE_OPCODE];

    if (!isValidOpcode(_opcode)) {
        return;
    }

    _arguments.assign(message.begin() + MESSAGE_OPCODE + 1, message.end());

    _isValid = true;
}

rtype::Packet::Packet(uint8_t opcode, Arguments arguments) : _isValid(false), _opcode(-1), _arguments({})
{
    _magicNumber = protocol::MAGIC;

    if (!isValidOpcode(opcode)) {
        return;
    }

    _opcode = opcode;
    _arguments = arguments;

    _isValid = true;
}

bool rtype::Packet::isValid() const
{
    return _isValid;
}

uint8_t rtype::Packet::getOpcode() const
{
    return _opcode;
}

rtype::Packet::Arguments rtype::Packet::getArguments() const
{
    return _arguments;
}

rtype::Packet::Message rtype::Packet::toMessage() const
{
    Message message;

    message.push_back(static_cast<uint8_t>((_magicNumber >> 24) & 0xFF));
    message.push_back(static_cast<uint8_t>((_magicNumber >> 16) & 0xFF));
    message.push_back(static_cast<uint8_t>((_magicNumber >> 8) & 0xFF));
    message.push_back(static_cast<uint8_t>(_magicNumber & 0xFF));

    message.push_back(_opcode);

    message.insert(message.end(), _arguments.begin(), _arguments.end());

    return message;
}

bool rtype::Packet::isValidOpcode(uint8_t opcode)
{
    for (size_t i = protocol::Operations::OPERATIONS_FIRST + 1; i < protocol::Operations::OPERATIONS_LENGTH; i++) {
        if (i == opcode) {
            return true;
        }
    }

    return false;
}
