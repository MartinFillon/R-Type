/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#ifndef GUI_HPP_
#define GUI_HPP_

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Network.hpp"
#include "IContext.hpp"
#include "Registry.hpp"
#include "ComponentFactory.hpp"

#define HOST 1
#define PORT 2
#define NB_ARGS 3
#define SUCCESS 0
#define ERROR 84

namespace rtype {

    class Gui : ecs::IContext {

        public:

            Gui(const std::string &host, const std::string &port);

            void start();

            int run() override;

            std::shared_ptr<ecs::Registry> &getRegistry() {
                return _r;
            };

        private:

            Network _network;

            void setupWeapon();
            void setupPlayer();
            void setupCollisons();
            void setupBackground();
            void setupBasicEnnemies();

            sf::RenderWindow _window;

            std::shared_ptr<ecs::Registry> _r;
            ecs::ComponentFactory _factory;

    };

};

#endif /* !GUI_HPP_ */
