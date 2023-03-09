#include "Raycast.h"

Raycast::Raycast(sf::RenderWindow& window)
{
    SCREEN_WIDTH = window.getSize().x;
    SCREEN_HEIGHT = window.getSize().y;
}

void Raycast::castRay(sf::RenderWindow& window, const sf::Vector2f& playerPos, sf::Vector2f playerDirection)
{
 
    sf::Vector2f cameraPlane = sf::Vector2f(-playerDirection.y, playerDirection.x);

    for (int i = 0; i < SCREEN_WIDTH; i++) {


        double cameraX = 2 * i / (double)SCREEN_WIDTH - 1;
        double rayDirX = playerDirection.x + cameraPlane.x * cameraX;
        double rayDirY = playerDirection.y + cameraPlane.y * cameraX;

        int mapX = static_cast<int>(playerPos.x);
        int mapY = static_cast<int>(playerPos.y);


        double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
        
        double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
        

        int stepX = (rayDirX < 0) ? -1 : 1;
        int stepY = (rayDirY < 0) ? -1 : 1;
        double sideDistX;
        double sideDistY;
        


        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (playerPos.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - playerPos.x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (playerPos.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - playerPos.y) * deltaDistY;
        }


        int hit = 0;
        int side = 0;
 
        while (hit == 0)
        {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (Minimap::Map[unsigned int(mapY / Minimap::cellSize.y)][unsigned int(mapX / Minimap::cellSize.x)] > 0 ) {
                hit = 1;
            }
        }

        double perpWallDist = 0.0;
        if (side == 0) {
            perpWallDist = (sideDistX - deltaDistX) / 10;
        }
        else {
            perpWallDist = (sideDistY - deltaDistY) / 10;
        }
  
            float lineHeight = SCREEN_HEIGHT / perpWallDist;
            int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawStart < 0) drawStart = 0;
            int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

            sf::VertexArray line(sf::PrimitiveType::Lines, 2);
            line[0].position = sf::Vector2f(i, drawStart);
            line[1].position = sf::Vector2f(i, drawEnd);
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::Black;

            window.draw(line);

    }
}



Raycast::~Raycast() {}