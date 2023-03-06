#ifndef PLAYER_H
#define PLAYER_H


#include "MiniMap.h"

class Player {
	public:
		Player();
		void playerMove();
		void drawPlayer(sf::RenderWindow& window);
		static sf::FloatRect getBoundingBox();
		static sf::Vector2f getPlayerPosition();
		~Player();
	private:
		static sf::RectangleShape player;
		sf::Vector2f movement;
		const float speed;
};


#endif 
