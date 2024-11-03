/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Animations3D
*/

#ifndef ANIMATIONS3D_HPP_
#define ANIMATIONS3D_HPP_

#include <string>

namespace ecs {
    namespace component {

        enum AnimationType { DanceAnimation, DieAnimation, RunAnimation, WalkAnimation, JumpAnimation };

        struct Animations3D {
            std::string _pathToFile;
            bool _state;
            AnimationType _type;
            int _animCount;
            int _animFrameCounter;
        };
    }; // namespace component
}; // namespace ecs

#endif /* !ANIMATIONS3D_HPP_ */
