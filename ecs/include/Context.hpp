/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Context
*/

#ifndef CONTEXT_HPP_
    #define CONTEXT_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace ecs {

	class Context {
		public:
			Context(sf::RenderWindow &);
			~Context();

		    sf::RenderWindow &getRenderWindow();

		protected:
		private:
			sf::RenderWindow &_window;
	};
} // namespace ecs

#endif /* !CONTEXT_HPP_ */
