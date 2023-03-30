#include "MiniMap.h"

sf::RectangleShape Minimap::grid[Minimap::ROWS][Minimap::COLUMNS];
sf::Vector2f Minimap::cellSize = sf::Vector2f(10.f, 10.f);

const int Minimap::Map[ROWS][COLUMNS] = {
{3,3,3,3,4,3,3,3,3,3,3,3,3,4,3,3,3},
{3,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,3},
{3,3,3,3,3,3,3,3,3,0,0,3,3,3,3,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{4,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3},
{3,3,3,4,3,3,3,3,3,3,4,3,3,3,3,3,3}
};

void Minimap::drawMiniMap(sf::RenderWindow& window) {

    sf::Vector2f playerPosition = Player::getPlayerPosition();
    const int minimapSize = 7;
    int playerX = round(playerPosition.x / 10);
    int playerY = round(playerPosition.y / 10);
    const int size = 2 * minimapSize + 1;
    //Map
    for (int i = 0; i < size * size; ++i) {
        const int y = i / size - minimapSize;
        const int x = i % size - minimapSize;
        const int tileX = playerX + x;
        const int tileY = playerY + y;
        if (tileX >= COLUMNS || tileX < 0 || tileY >= ROWS || tileY < 0) continue;

        sf::RectangleShape tile;
        tile.setSize(cellSize);
        tile.setFillColor(Map[tileY][tileX] ? sf::Color::White : sf::Color::Black);
        tile.setPosition((minimapSize + x) * cellSize.x, (minimapSize + y) * cellSize.y);
        window.draw(tile);
    }

    // Player
    sf::RectangleShape player;
    player.setSize(cellSize);
    player.setFillColor(sf::Color::Green);
    player.setPosition(minimapSize * cellSize.x, minimapSize * cellSize.y);
    window.draw(player);

    // PlayerDirection
    sf::RectangleShape playerDir;
    const float centerX = minimapSize * cellSize.x + cellSize.x / 2;
    const float centerY = minimapSize * cellSize.y + cellSize.y / 2;
    const float direction = atan2(Player::getDirection().y, Player::getDirection().x);
    playerDir.setSize(sf::Vector2f(5.f, 5.f));
    playerDir.setFillColor(sf::Color::Red);
    playerDir.setPosition(centerX + cos(direction) * 5.f - 2.5, centerY + sin(direction) * 5.f - 2.5);
    window.draw(playerDir);
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