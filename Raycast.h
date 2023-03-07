#ifndef RAYCAST_H
#define RAYCAST_H

#include <SFML/Graphics.hpp>
#include "Player.h"
class Raycast {
	public:
		Raycast(sf::RenderWindow& window);
		void castRay(sf::RenderWindow& window);
		~Raycast();
	private:
		float FOV;
		unsigned int SCREEN_WIDTH;
		unsigned int SCREEN_HEIGHT;
		Player player;
};

#endif

