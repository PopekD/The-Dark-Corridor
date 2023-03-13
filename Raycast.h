#ifndef RAYCAST_H
#define RAYCAST_H

#include <SFML/Graphics.hpp>
#include "MiniMap.h"

class Raycast {
	public:
		Raycast(sf::RenderWindow& window);
		void initializeTextures();
		void castRay(sf::RenderWindow& window, const sf::Vector2f& playerPos,const sf::Vector2f& playerDirection);
		void drawCeilingandFloor(sf::RenderWindow& window);
		~Raycast();
	private:
		unsigned int SCREEN_WIDTH;
		unsigned int SCREEN_HEIGHT;
		sf::Texture textures[4];
		sf::Sprite floorSprite;
		sf::Sprite ceilingSprite;
		sf::VertexArray lines;
		const int wallSize = 256;
};

#endif

