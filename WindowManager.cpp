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

    while (window.isOpen()) {
        sf::Event event;


        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        player.playerMove();
        window.clear(sf::Color::Blue);
        minimap.drawMiniMap(window);
        player.drawPlayer(window);
        //raycast.castRay(window);
        window.display();
    }
}