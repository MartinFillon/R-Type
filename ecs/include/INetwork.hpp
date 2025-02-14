/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** INetwork
*/

#ifndef INETWORK_HPP_
#define INETWORK_HPP_

#include <memory>
#include "IPacket.hpp"

namespace ecs {
    class IContext;

    class INetwork {
      public:
        virtual ~INetwork() = default;

        /// @brief Broadcasts the given `packet` to all the currently connected clients.
        /// @param packet a `const Packet &` representing the reference to the packet to be sent to all the currently
        /// connected clients.
        virtual void broadcast(const IPacket &packet) = 0;

        /// @brief Runs the server
        /// @return Always `EXIT_SUCCESS` for now.
        virtual int run(std::shared_ptr<IContext> &) = 0;

      protected:
      private:
    };
} // namespace ecs
#endif /* !INETWORK_HPP_ */
