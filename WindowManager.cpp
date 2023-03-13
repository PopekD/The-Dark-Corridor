#include "WindowManager.h"
#include <chrono>
WindowManager::WindowManager() 
{
    window.create(sf::VideoMode(1280, 720), "Game");
    try
    {
        inputTexture.loadFromFile("pixels.png");
        inputSprite.setTexture(inputTexture);
        float scaleX = window.getSize().x / inputSprite.getLocalBounds().width;
        float scaleY = window.getSize().y / inputSprite.getLocalBounds().height;
        inputSprite.setScale(scaleX, scaleY);
        inputSprite.setColor(sf::Color(255, 255, 255, 13));
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }
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
    window.setFramerateLimit(240.0f);
    std::chrono::steady_clock::time_point lastUpdate = std::chrono::steady_clock::now();

    raycast.initializeTextures();

    while (window.isOpen()) {

        sf::Event event;

        auto NOW = std::chrono::steady_clock::now();
        float deltT = std::chrono::duration_cast<std::chrono::milliseconds>(NOW - lastUpdate).count();
        lastUpdate = NOW;


        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Mouse::setPosition(center, window);
        sf::Vector2i mouseDiff = mousePosition - center;

        float angle = 0.0f;
        if (mouseDiff.x < 0) {
            angle = -0.2f * deltT;
        }
        else if (mouseDiff.x > 0) {
            angle = 0.2f * deltT;
        }


        window.clear();

        raycast.drawCeilingandFloor(window);

        raycast.castRay(window, player.getPlayerPosition(), player.getDirection());
        window.draw(inputSprite);
        minimap.drawMiniMap(window);
        player.drawPlayer(window);
        player.playerMove(window, angle, deltT);

        window.display();

    }
}