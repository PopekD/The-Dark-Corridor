#include "Raycast.h"

Raycast::Raycast(sf::RenderWindow& window)
{
    SCREEN_WIDTH = window.getSize().x;
    SCREEN_HEIGHT = window.getSize().y;
    lines = sf::VertexArray(sf::Lines, 18 * SCREEN_WIDTH);
}

void Raycast::initializeTextures() {
    
    try
    {
        textures[0].loadFromFile("floor.jpg");
        textures[1].loadFromFile("sky.jpg");
        textures[2].loadFromFile("wall.jpg");
        textures[3].loadFromFile("brick.jpg");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }

    ceilingSprite.setTexture(textures[1]);
    floorSprite.setTexture(textures[0]);

}

void Raycast::drawCeilingandFloor(sf::RenderWindow& window)
{
    ceilingSprite.setPosition(0, 0);
    ceilingSprite.setScale(float(SCREEN_WIDTH) / textures[1].getSize().x, float((SCREEN_HEIGHT / 2)) / textures[1].getSize().y);

    floorSprite.setPosition(0, float((SCREEN_HEIGHT / 2)));
    floorSprite.setScale(float(SCREEN_WIDTH) / textures[0].getSize().x, float((SCREEN_HEIGHT / 2)) / textures[0].getSize().y);


    window.draw(ceilingSprite);
    window.draw(floorSprite);
}

void Raycast::castRay(sf::RenderWindow& window, const sf::Vector2f& playerPos, const sf::Vector2f& playerDirection)
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

            
            int texNum = Minimap::Map[unsigned int(mapY / Minimap::cellSize.y)][unsigned int(mapX / Minimap::cellSize.x)] - 1;


            double wallX; //where exactly the wall was hit
            if (side == 0) wallX = (playerPos.y / Minimap::cellSize.y) + perpWallDist * rayDirY;
            else           wallX = (playerPos.x / Minimap::cellSize.x)+ perpWallDist * rayDirX;
            wallX -= floor((wallX));

            //x coordinate on the texture
            int texX = int(wallX * double(wallSize));
            if (side == 0 && rayDirX > 0) texX = wallSize - texX - 1;
            if (side == 1 && rayDirY < 0) texX = wallSize - texX - 1;

            double step = Minimap::cellSize.y * wallSize / lineHeight;
            double texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;

            int texY = (int)texPos & (textures[texNum].getSize().y - 1);
            texPos += step;



            lines.append(sf::Vertex(
                sf::Vector2f((float)i, (float)drawStart),
                sf::Vector2f((float)texX, (float)texY + 1)
            ));
            lines.append(sf::Vertex(
                sf::Vector2f((float)i, (float)drawEnd),
                sf::Vector2f((float)texX, (float)(texY + wallSize - 1))
            ));
        

            if (side == 1)
            {
                lines[0].color = sf::Color(128, 128, 128);
                lines[1].color = sf::Color(128, 128, 128);
            }

            window.draw(lines, &textures[texNum]);
            lines.clear();
    }

}



Raycast::~Raycast() {}