/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-1-rtype-edward.lalande
** File description:
** Packet
*/

#ifndef PACKET_HPP_
#define PACKET_HPP_

#include <memory>
#include <vector>

#define MESSAGE_OPCODE 4
#define MESSAGE_MIN_SIZE 5
#define GET_MAGIC_NUMBER(x) (x[0] << 24) | (x[1] << 16) | (x[2] << 8) | x[3]

namespace Rtype {

    class Packet {

        using Message = std::vector<uint8_t>;
        using Arguments = std::vector<uint8_t>;

      public:
        Packet(const Message &message);
        Packet(uint8_t opcode, Arguments arguments = {});

        bool isValid() const;
        uint8_t getOpcode() const;
        Arguments getArguments() const;

        Message toMessage() const;

      private:
        bool isValidOpcode(uint8_t opcode);

        bool _isValid;

        uint32_t _magicNumber;
        uint8_t _opcode;
        Arguments _arguments;
    };

}; // namespace Rtype

#endif /* !PACKET_HPP_ */
