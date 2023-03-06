#ifndef MINIMAP_H
#define MINIMAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Minimap {
public:
    void drawMiniMap(sf::RenderWindow& window);
    void initMiniMap(sf::RenderWindow& window);
    static const int ROWS = 16;
    static const int COLUMNS = 18;
    static const int Map[ROWS][COLUMNS];
    static sf::FloatRect getBoundingBox(int i, int j);
private:
    sf::Vector2f cellSize;
    static sf::RectangleShape grid[ROWS][COLUMNS];
};


#endif
