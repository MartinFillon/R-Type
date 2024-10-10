/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#define SECONDS_TO_MILISECONDS 1000
#define SECONDS_TO_MICROSECONDS 1000000

#include <chrono>

namespace ecs {

    /// @brief Clock encapsulation to get a Clock and not an sf::Clock
    class Clock {
      public:
        /// @brief Constructor of Clock, start a clock in his constructor
        Clock()
        {
            _start = std::chrono::system_clock::now();
        }

        /// @brief restart method, reset the clock
        void restart()
        {
            _start = std::chrono::system_clock::now();
        }

        /// @brief getSeconds time elapsed since the last start
        /// @return the time as a double of the time elapsed since the last start, return it as seconds
        double getSeconds()
        {
            return std::chrono::duration<double>(std::chrono::system_clock::now() - _start).count();
        }

        /// @brief getMiliSeconds time elapsed since the last start
        /// @return the time as a double of the time elapsed since the last start, return it as Miliseconds
        double getMiliSeconds()
        {
            return std::chrono::duration<double>(std::chrono::system_clock::now() - _start).count() *
                SECONDS_TO_MILISECONDS;
        }

        /// @brief getMiliSeconds time elapsed since the last start
        /// @return the time as a double of the time elapsed since the last start, return it as MicroSeconds
        double getMicroSeconds()
        {
            return std::chrono::duration<double>(std::chrono::system_clock::now() - _start).count() *
                SECONDS_TO_MICROSECONDS;
        }

      private:
        /// @brief is the chrono of the class
        std::chrono::time_point<std::chrono::system_clock> _start;
    };

}; // namespace ecs

#endif /* !CLOCK_HPP_ */
