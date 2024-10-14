/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** IPacket
*/

#ifndef IPACKET_HPP_
#define IPACKET_HPP_

#include <cstdint>
#include <vector>

namespace ecs {
    class IPacket {
        using Message = std::vector<uint8_t>;
        using Arguments = std::vector<uint8_t>;

      public:
        virtual ~IPacket() = default;

        /// @brief Checks if the packet is valid and ready to be sent or not.
        /// @return `true` if the packet is valid and ready to be sent to the client or `false` if not.
        virtual bool isValid() const = 0;
        /// @brief Get the operation code of the packet.
        /// @return `uint8_t` equal to a `protocol::Operations::*` if the operation code of the packet is valid or -1 if
        /// it's not.
        virtual uint8_t getOpcode() const = 0;
        /// @brief Get the arguments of the packet.
        /// @return `Arguments` aka `std::vector<uint8_t>` of the packet. The returned value is always at least an empty
        /// vector.
        virtual Arguments getArguments() const = 0;

        /// @brief Translates the packet to an understandable message for the upd socket aka the operation code
        /// concatenated with the arguments.
        /// @return `Message` aka `std::vector<uint8_t>` of the complete message.
        virtual Message toMessage() const = 0;

      protected:
      private:
    };
} // namespace ecs

#endif /* !IPACKET_HPP_ */
