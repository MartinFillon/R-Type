/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Invincibility
*/

#ifndef INVINCIBILITY_HPP_
#define INVINCIBILITY_HPP_

#include <sstream>
#include <string>
#include "Clock.hpp"
#include "IComponent.hpp"

namespace ecs {
    namespace component {
        struct Invincibility : public IComponent {
            Invincibility(bool invicible, int time, ecs::Clock clock): _invincible(invicible), _time_in_ms(time), _clock(clock) {}
            Invincibility() = default;
            bool _invincible;
            int _time_in_ms;
            ecs::Clock _clock;
            std::string _name = "Invincibility";
            std::string getName() const {
                return _name;
            }
            std::string getInfo() const {
                std::ostringstream stream;

                stream << "Invincible: " << std::string(_invincible ? "true": "false") << " time: " <<  _time_in_ms;

                return stream.str();
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !INVINCIBILITY_HPP_ */
