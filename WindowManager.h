#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "MiniMap.h"
#include "Player.h"
#include "Raycast.h"
#include <string>

class WindowManager {
    public:
        WindowManager();
        void setWindow(int WIDTH, int HEIGHT, std::string TITLE);
        void run();
    private:
        sf::RenderWindow window;
        Minimap minimap;
        Player player;
        sf::Texture inputTexture;
        sf::Sprite inputSprite;
};

#endif