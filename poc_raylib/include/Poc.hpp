/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Poc
*/

#ifndef POC_HPP_
#define POC_HPP_

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define PATH_TO_POC_ASSETS_MODEL "poc_raylib/assets/Model/"
#define PATH_TO_POC_ASSETS_SPRITES "poc_raylib/assets/Sprites/"

#include <memory>
#include <raylib.h>
#include "ComponentFactory.hpp"
#include "Registry.hpp"

namespace poc {
    class Poc {
        public:
            Poc(int fps);
            ~Poc();
            int run();

            void draw();

            void handleMouvement();

            std::size_t findPlayerIndex();

        private:
            std::shared_ptr<ecs::Registry> _r;
            ecs::ComponentFactory _cf;
            Camera _camera;
    };
}

#endif /* !POC_HPP_ */
