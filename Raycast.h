#ifndef RAYCAST_H
#define RAYCAST_H

#include <SFML/Graphics.hpp>
#include "MiniMap.h"

class Raycast {
	public:
		Raycast(sf::RenderWindow& window);
		void initializeTextures();
		void castRay(sf::RenderWindow& window, const sf::Vector2f& playerPos,const sf::Vector2f& playerDirection);
		~Raycast();
	private:
		unsigned int SCREEN_WIDTH;
		unsigned int SCREEN_HEIGHT;
		sf::Texture textures[5];
		sf::VertexArray lines;
		sf::Sprite desksprite;
		sf::VertexArray floorlines;
		const float maxRenderDistance = 40.0f;
		const int wallSize = 256;
};

#endif

