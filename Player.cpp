#include "Player.h"
#include <iostream>

sf::RectangleShape Player::player;

Player::Player(): speed(0.10f) {
    player.setSize(sf::Vector2f(10.0f, 10.0f));
	player.setPosition(sf::Vector2f(50.0f, 50.0f));
    player.setFillColor(sf::Color::Red);
}
void Player::playerMove()
{
    movement.x = 0.f;
    movement.y = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        movement.x -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        movement.x += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        movement.y -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        movement.y += speed;
    }

    if (movement.x != 0.f && movement.y != 0.f)
    {
        movement /= std::sqrt(2.f);
    }

    for (int i = 0; i < Minimap::ROWS; i++) {
        for (int j = 0; j < Minimap::COLUMNS; j++) {
            if (Minimap::Map[i][j] == 1) {
      
                sf::FloatRect playerBounds = getBoundingBox();
                sf::FloatRect wallBounds = Minimap::getBoundingBox(i, j);
                
                if (playerBounds.intersects(wallBounds)) {
                    
                    sf::Vector2f mtv;
                    sf::Vector2f playerCenter = sf::Vector2f(playerBounds.left + playerBounds.width / 2.0f,
                        playerBounds.top + playerBounds.height / 2.0f);
                    sf::Vector2f wallCenter = sf::Vector2f(wallBounds.left + wallBounds.width / 2.0f,
                        wallBounds.top + wallBounds.height / 2.0f);
                    sf::Vector2f centersDelta = playerCenter - wallCenter;
                    float xOverlap = (playerBounds.width + wallBounds.width) / 2.0f - std::abs(centersDelta.x);
                    float yOverlap = (playerBounds.height + wallBounds.height) / 2.0f - std::abs(centersDelta.y);
                    if (xOverlap > 0 && yOverlap > 0) {
                        if (xOverlap < yOverlap) {
                            mtv = (centersDelta.x > 0) ? sf::Vector2f(xOverlap, 0) : sf::Vector2f(-xOverlap, 0);
                        }
                        else {
                            mtv = (centersDelta.y > 0) ? sf::Vector2f(0, yOverlap) : sf::Vector2f(0, -yOverlap);
                        }
                       
                        player.move(mtv);
                    }
                }
            }
        }
                
    }
    player.move(movement);
   
}

sf::FloatRect Player::getBoundingBox() {
    return player.getGlobalBounds();
}
sf::Vector2f Player::getPlayerPosition() {
    sf::FloatRect playerBounds = getBoundingBox();
    return sf::Vector2f(playerBounds.left + playerBounds.width / 2.0f, playerBounds.top + playerBounds.height / 2.0f);
}


void Player::drawPlayer(sf::RenderWindow& window)
{
    window.draw(player);
}

Player::~Player() {}