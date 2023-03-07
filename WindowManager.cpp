#include "WindowManager.h"

WindowManager::WindowManager() 
{
    window.create(sf::VideoMode(1280, 720), "Game");
}

void WindowManager::setWindow(int WIDTH, int HEIGHT, std::string TITLE)
{
    window.create(sf::VideoMode(WIDTH, HEIGHT), TITLE);
}


void WindowManager::run() {

    minimap.initMiniMap(window);
    window.setMouseCursorVisible(true);
    window.setMouseCursorGrabbed(true);


    sf::Vector2i center(window.getSize().x / 2, window.getSize().y / 2);
    Raycast raycast(window);
    window.setFramerateLimit(60.0f);

    while (window.isOpen()) {

        sf::Event event;
        

        sf::Vector2i prevMousePosition = sf::Mouse::getPosition(window);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2i mouseDiff = mousePosition - prevMousePosition;

        float direction = 0.0f;
        if (mouseDiff.x < 0) {
            direction = -5.0f;
        }
        else if (mouseDiff.x > 0) {
            direction = 5.0f;
        }


        player.playerMove(window, direction);

        prevMousePosition = mousePosition;

        sf::Mouse::setPosition(center, window);

        window.clear(sf::Color::Blue);
        minimap.drawMiniMap(window);
        player.drawPlayer(window);
        raycast.castRay(window);
        window.display();

    }
}