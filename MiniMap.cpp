#include "MiniMap.h"

sf::RectangleShape Minimap::grid[Minimap::ROWS][Minimap::COLUMNS];
sf::Vector2f Minimap::cellSize = sf::Vector2f(10.0f, 10.0f);

const int Minimap::Map[ROWS][COLUMNS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

};

void Minimap::drawMiniMap(sf::RenderWindow& window) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = COLUMNS-1; j >= 0; j--) {
            window.draw(grid[i][j]);
        }
    }
}
void Minimap::initMiniMap(sf::RenderWindow& window) {

    for (int i = 0;i < ROWS;i++) {
        for (int j = 0;j < COLUMNS;j++) {
            grid[i][j].setSize(cellSize);
            if (Map[i][j] == 1) {
                grid[i][j].setFillColor(sf::Color::White);
            }
            else {
                grid[i][j].setFillColor(sf::Color::Black);
            }
            grid[i][j].setPosition(j * cellSize.x, i * cellSize.y);
        }
    }

}

sf::FloatRect Minimap::getBoundingBox(int i, int j) {
    return grid[i][j].getGlobalBounds();
}