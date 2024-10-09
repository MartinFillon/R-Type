/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** DestroySystem
*/

#ifndef DESTROYSYSTEM_HPP_
#define DESTROYSYSTEM_HPP_

#define DESTROY_SPRITE "r-typesheet-explosion.gif"

#define DESTROY_ANIMATION 0.1
#define DESTROY_TICK 1

#include "Components/Animations.hpp"
#include "Components/Destroyable.hpp"
#include "Components/Sprite.hpp"
#include "ISystems.hpp"
#include "Registry.hpp"
#include "ZipperIterator.hpp"

namespace ecs {
    namespace systems {
        class DestroySystem : public ISystems {
          public:
            void operator()(Registry &r)
            {
                if (_clock.getMiliSeconds() < DESTROY_TICK) {
                    return;
                }
                _clock.restart();
                auto &destroyables = r.get_components<ecs::component::Destroyable>();
                auto &animations = r.get_components<ecs::component::Animations>();
                auto &sprites = r.get_components<ecs::component::Sprite>();
                int idx = 0;

                for (auto &&[anim, destroy, sprite] : ecs::custom_zip(animations, destroyables, sprites)) {
                    if (!anim || !destroy || !sprite || !destroy->_destroyable) {
                        idx += 1;
                        continue;
                    }

                    if (sprite->_pathToSprite != DESTROY_SPRITE) {
                        sprite->_pathToSprite = DESTROY_SPRITE;
                        anim->_x = 0;
                        anim->_y = 0;
                        anim->_width = 65;
                        anim->_height = 65;
                        anim->_clock.restart();
                        continue;
                    }

                    if (anim->_x > 315) {
                        r.erase(idx);
                    }

                    if (anim->_clock.getSeconds() > DESTROY_ANIMATION) {
                        anim->_x += anim->_width;
                        anim->_clock.restart();
                    }
                    idx += 1;
                }
            }

          private:
            Clock _clock;
        };
    }; // namespace systems
}; // namespace ecs

#endif /* !DESTROYSYSTEM_HPP_ */
