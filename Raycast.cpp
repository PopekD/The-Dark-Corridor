#include "Raycast.h"

Raycast::Raycast(sf::RenderWindow& window)
{
	FOV = 60.0f;
	SCREEN_WIDTH = window.getSize().x;
	SCREEN_HEIGHT = window.getSize().y;
}

void Raycast::castRay(sf::RenderWindow& window)
{

}


Raycast::~Raycast(){}