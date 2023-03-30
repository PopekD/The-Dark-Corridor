#ifndef MINIMAP_H
#define MINIMAP_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
#include <vector>

class Minimap {
public:
    void drawMiniMap(sf::RenderWindow& window);
    void initMiniMap(sf::RenderWindow& window);
    static const int ROWS = 11;
    static const int COLUMNS = 17;
    static const int Map[ROWS][COLUMNS];
    static sf::Vector2f cellSize;
    static sf::FloatRect getBoundingBox(int i, int j);
private:
    static sf::RectangleShape grid[ROWS][COLUMNS];
    
};


#endif

