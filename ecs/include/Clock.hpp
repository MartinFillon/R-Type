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

    /// @brief Class to wrap all the utilities of the system's clock.
    class Clock {
      public:
        /// @brief Generates a `Clock` and starts it by setting its start time to now.
        Clock()
        {
            _start = std::chrono::system_clock::now();
        }

        /// @brief Sets the clock's start time to now.
        void restart()
        {
            _start = std::chrono::system_clock::now();
        }

        /// @brief Get the elapsed time since the clock's start time in seconds.
        /// @return `double` representing the elapsed time since the clock's start time in seconds.
        double getSeconds()
        {
            return std::chrono::duration<double>(std::chrono::system_clock::now() - _start).count();
        }

        /// @brief Get the elapsed time since the clock's start time in milliseconds.
        /// @return `double` representing the elapsed time since the clock's start time in milliseconds.
        double getMilliSeconds()
        {
            return std::chrono::duration<double>(std::chrono::system_clock::now() - _start).count() *
                SECONDS_TO_MILISECONDS;
        }

        /// @brief Get the elapsed time since the clock's start time in microseconds.
        /// @return `double` representing the elapsed time since the clock's start time in microseconds.
        double getMicroSeconds()
        {
            return std::chrono::duration<double>(std::chrono::system_clock::now() - _start).count() *
                SECONDS_TO_MICROSECONDS;
        }

      private:
        /// @brief The clock's start time.
        std::chrono::time_point<std::chrono::system_clock> _start;
    };

}; // namespace ecs

#endif /* !CLOCK_HPP_ */
