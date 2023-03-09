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
    window.setMouseCursorVisible(false);


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

        float angle = 0.0f;
        if (mouseDiff.x < 0) {
            angle = -5.0f;
        }
        else if (mouseDiff.x > 0) {
            angle = 5.0f;
        }


        player.playerMove(window, angle);

        prevMousePosition = mousePosition;

        sf::Mouse::setPosition(center, window);

        window.clear(sf::Color::Blue);
        raycast.castRay(window, player.getPlayerPosition());
        minimap.drawMiniMap(window);
        player.drawPlayer(window);
        window.display();

    }
}