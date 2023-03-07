#ifndef PLAYER_H
#define PLAYER_H


#include "MiniMap.h"
#include <cmath>
const double M_PI = std::acos(-1);

class Player {
	public:
		Player();
		void playerMove(sf::RenderWindow& window, float angle);
		void drawPlayer(sf::RenderWindow& window);
		static sf::Vector2f getPlayerPosition();
		static sf::FloatRect getBoundingBox();
		~Player();
	private:
		static sf::RectangleShape player;
		static sf::Vector2f movement;
		static float speed;
		static float rotation;
};


#endif 
