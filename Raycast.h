#ifndef RAYCAST_H
#define RAYCAST_H

#include <SFML/Graphics.hpp>
#include "MiniMap.h"

class Raycast {
	public:
		Raycast(sf::RenderWindow& window);
		void castRay(sf::RenderWindow& window, const sf::Vector2f& playerPos, sf::Vector2f playerDirection);
		~Raycast();
	private:
		unsigned int SCREEN_WIDTH;
		unsigned int SCREEN_HEIGHT;
};

#endif

