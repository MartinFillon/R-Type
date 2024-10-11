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

namespace ecs {

    /// @brief Class to wrap all the utilities of the communication packets to send to the client.
    class Packet {

        using Message = std::vector<uint8_t>;
        using Arguments = std::vector<uint8_t>;

      public:
        /// @brief Generates a `Packet` to send to the client. To verify if the generated `Packet` is valid, check its
        /// `isValid()` fucntion.
        /// @param message a `Message` aka `std::vector<uint8_t>` of bits to package.
        /// @deprecated use `Packet(uint8_t opcode, Arguments arguments = {})` instead.
        Packet(const Message &message);
        /// @brief Generates a `Packet` to send to the client. To verify if the generated `Packet` is valid, check its
        /// `isValid()` fucntion.
        /// @param opcode an `uint8_t` representing an operation code. A valid operation code come from
        /// `protocol::Operations::*`.
        /// @param arguments an `Argument` aka `std::vector<uint8_t>` representing the bitshifted parameters to send to
        /// the client.
        Packet(uint8_t opcode, Arguments arguments = {});

        /// @brief Checks if the packet is valid and ready to be sent or not.
        /// @return `true` if the packet is valid and ready to be sent to the client or `false` if not.
        bool isValid() const;
        /// @brief Get the operation code of the packet.
        /// @return `uint8_t` equal to a `protocol::Operations::*` if the operation code of the packet is valid or -1 if
        /// it's not.
        uint8_t getOpcode() const;
        /// @brief Get the arguments of the packet.
        /// @return `Arguments` aka `std::vector<uint8_t>` of the packet. The returned value is always at least an empty
        /// vector.
        Arguments getArguments() const;

        /// @brief Translates the packet to an understandable message for the upd socket aka the operation code
        /// concatenated with the arguments.
        /// @return `Message` aka `std::vector<uint8_t>` of the complete message.
        Message toMessage() const;

      private:
        /// @brief Checks if the given operation code is in the `protocol::Operations` enum
        /// @param opcode an `uint8_t` representing the operation code to check
        /// @return `true` if the operation code is in the `protocol::Operations` enum or `false` if not
        bool isValidOpcode(uint8_t opcode);

        /// @brief `true` means that the packet is valid and ready to be sent to the client, `false` means that the
        /// package is not valid and cannot be sent to the client
        bool _isValid;

        /// @brief The magic number needed by the client to understand the beginning of a received packet
        uint32_t _magicNumber;
        /// @brief The operation code from the `protocol::Operations` enum of the packet
        uint8_t _opcode;
        /// @brief The vector of arguments of the packet
        Arguments _arguments;
    };

}; // namespace ecs

#endif /* !PACKET_HPP_ */
