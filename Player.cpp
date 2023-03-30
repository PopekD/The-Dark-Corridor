#include "Player.h"
#include <iostream>

sf::RectangleShape Player::player;
float Player::speed = 0.02f;
sf::Vector2f Player::movement(0.f, 0.f);
float Player::rotation = 0.0f;
sf::Vector2f Player::direction;
bool Player::movingUp = true;
Player::Player() {
    player.setSize(sf::Vector2f(06.f, 06.f));
	player.setPosition(sf::Vector2f(20.0f, 60.0f));
    player.setFillColor(sf::Color::Green);
    this->movingUp = true;
}
void Player::playerMove(sf::RenderWindow& window, float angle, float dt)
{
    
    player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2);
        
        rotation += angle;
        if (rotation >= 360){

            rotation -= 360;
        }
        else if(rotation <= -360)
        {
            rotation += 360;
        }

        player.setRotation(rotation);
    

    float radians = rotation * M_PI / 180;

    direction = sf::Vector2f(std::cos(radians), std::sin(radians));
    direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);
   
    movement.x = 0.f;
    movement.y = 0.f;

    float speedDelta = speed * dt;
    float handSpeed;

    if (movingUp) {   
        handSpeed = -speed * dt;
        if (handSprite.getPosition().y < initialPosition - 20.0f) {
            movingUp = false;
        }
    }
    else {
        handSpeed = speedDelta;
        if (handSprite.getPosition().y > initialPosition) {
            movingUp = true;
        }
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        if (direction != sf::Vector2f(0, 0)) {
            movement += direction * speedDelta;
            handSprite.move(sf::Vector2f(0.0f, handSpeed ));
        }
        else {
            movement.y -= speedDelta;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        if (direction != sf::Vector2f(0, 0)) {
            movement -= direction * speedDelta;
            handSprite.move(sf::Vector2f(0.0f, handSpeed));
        }
        else {
            movement.y += speedDelta;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        if (direction != sf::Vector2f(0, 0)) {
            sf::Vector2f horizontalDirection(-direction.y, direction.x);
            movement -= horizontalDirection * speedDelta;
           
        }
        else {
            movement.x -= speedDelta;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        if (direction != sf::Vector2f(0, 0)) {
            sf::Vector2f horizontalDirection(-direction.y, direction.x);
            movement += horizontalDirection * speedDelta;

        }
        else {
            movement.x += speedDelta;
        }
    }

    if (movement.x != 0.f && movement.y != 0.f)
    {
        movement /= std::sqrt(2.f);
    }

    for (int i = 0; i < Minimap::ROWS; i++) {
        for (int j = 0; j < Minimap::COLUMNS; j++) {
            if (Minimap::Map[i][j] != 0) {
      
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
sf::Vector2f Player::getDirection() {
    return direction;
};

void Player::initHand(sf::RenderWindow& window) {
    try
    {
        hand.loadFromFile("Assets/hand.png");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }

    this->handSprite = sf::Sprite(hand);
    handSprite.setOrigin(sf::Vector2f(hand.getSize().x, hand.getSize().y));
    handSprite.setPosition(sf::Vector2f(window.getSize().x, window.getSize().y));
    initialPosition = handSprite.getPosition().y;
    if (window.getSize().x < 1920) {
        handSprite.setScale(sf::Vector2f(0.7f, 0.7f));
    }
}
void Player::drawHand(sf::RenderWindow& window) {
    window.draw(handSprite);
}
sf::Vector2f Player::getHandPosition() {
    return handSprite.getPosition();
}


Player::~Player() {}