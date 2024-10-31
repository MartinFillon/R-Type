/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include <chrono>
#include "Defs.hpp"

namespace ecs {

    class Clock {
      public:
        Clock()
        {
            _start = std::chrono::system_clock::now();
        }

        void restart()
        {
            _start = std::chrono::system_clock::now();
        }

        double getSeconds()
        {
            return std::chrono::duration<double>(std::chrono::system_clock::now() - _start).count();
        }

        double getMiliSeconds()
        {
            return std::chrono::duration<double>(std::chrono::system_clock::now() - _start).count() *
                SECONDS_TO_MILISECONDS;
        }

        double getMicroSeconds()
        {
            return std::chrono::duration<double>(std::chrono::system_clock::now() - _start).count() *
                SECONDS_TO_MICROSECONDS;
        }

      private:
        std::chrono::time_point<std::chrono::system_clock> _start;
    };

}; // namespace ecs

#endif /* !CLOCK_HPP_ */
