#ifndef PLAYER_H
#define PLAYER_H


#include "MiniMap.h"

const double M_PI = std::acos(-1);

class Player {
	public:
		Player();
		void playerMove(sf::RenderWindow& window, float angle, float dt);
		static sf::Vector2f getPlayerPosition();
		static sf::FloatRect getBoundingBox();
		static sf::Vector2f getDirection();
		void initHand(sf::RenderWindow& window);
		void drawHand(sf::RenderWindow& window);
		sf::Vector2f getHandPosition();
		~Player();
	private:
		static sf::RectangleShape player;
		static sf::Vector2f movement;
		static float speed;
		static float rotation;
		static sf::Vector2f direction;
		sf::Texture hand;
		sf::Sprite handSprite;
		float initialPosition;
		static bool movingUp;
};


#endif 
