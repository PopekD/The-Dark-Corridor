#include "WindowManager.h"
#include <chrono>
WindowManager::WindowManager() 
{
    window.create(sf::VideoMode(1920, 1080), "Game", sf::Style::Fullscreen);
    try
    {
        inputTexture.loadFromFile("Assets/pixels.png");
        inputSprite.setTexture(inputTexture);

        float scaleX = window.getSize().x / inputSprite.getLocalBounds().width;
        float scaleY = window.getSize().y / inputSprite.getLocalBounds().height;

        inputSprite.setScale(scaleX, scaleY);
        inputSprite.setColor(sf::Color(255, 255, 255, 6));
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
    player.initHand(window);

    sf::Vector2f handPosition = player.getHandPosition();
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



        window.clear(sf::Color(22, 22, 29, 255));
        raycast.castRay(window, player.getPlayerPosition(), player.getDirection());
        player.drawHand(window);
        window.draw(inputSprite);
        minimap.drawMiniMap(window);
        player.playerMove(window, angle, deltT);

        window.display();

    }
}