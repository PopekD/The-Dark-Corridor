#include "Player.h"
#include <iostream>

sf::RectangleShape Player::player;
float Player::speed = 1.0f;
sf::Vector2f Player::movement(0.f, 0.f);
float Player::rotation = 0.0f;
Player::Player() {
    player.setSize(sf::Vector2f(09.0f, 09.0f));
	player.setPosition(sf::Vector2f(30.0f, 30.0f));
    player.setFillColor(sf::Color::Green);
    
}
void Player::playerMove(sf::RenderWindow& window, float angle)
{
    
    player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2);
    
    rotation += angle;
    player.setRotation(rotation);

    float radians = rotation * M_PI / 180;

    sf::Vector2f direction(std::cos(radians), std::sin(radians));
    direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);

    movement.x = 0.f;
    movement.y = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        movement += sf::Vector2f(direction.y, -direction.x) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        movement -= sf::Vector2f(direction.y, -direction.x) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        movement += direction * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        movement -= direction * speed;
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
    return player.getPosition();
}



void Player::drawPlayer(sf::RenderWindow& window)
{
    window.draw(player);
}

Player::~Player() {}