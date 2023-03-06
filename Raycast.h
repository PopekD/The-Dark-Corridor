#ifndef RAYCAST_H
#define RAYCAST_H

#include <SFML/Graphics.hpp>
#include "Player.h"
class Raycast {
	public:
		Raycast();
		//void castRay(sf::RenderWindow& window);
		~Raycast();
	private:
		float playerAngle;
};

#endif

