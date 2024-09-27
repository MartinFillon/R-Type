/*
** EPITECH PROJECT, 2024
<<<<<<< HEAD
** rtype
=======
** R-Type
>>>>>>> master
** File description:
** Context
*/

<<<<<<< HEAD
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace ECS {

class Context {
  public:
    Context(sf::RenderWindow &);
    ~Context();

    sf::RenderWindow &getRenderWindow();

  protected:
  private:
    sf::RenderWindow &_window;
};
} // namespace ECS
=======
#ifndef CONTEXT_HPP_
    #define CONTEXT_HPP_

    #include <SFML/Graphics.hpp>
    #include <SFML/Graphics/RenderWindow.hpp>
    #include "EntityManager.hpp"
    #include "Registry.hpp"
namespace ecs {

	class Context {
		public:
			Context();
			~Context();

		    sf::RenderWindow &getRenderWindow();

                    int run();
		protected:

                private:
                    void setup();
                    void setupPlayer();
                    void setupBackground();
                    sf::RenderWindow _window;
                    EntityManager _entitys;
                    Registry _r;
	};
} // namespace ecs

#endif /* !CONTEXT_HPP_ */
>>>>>>> master
