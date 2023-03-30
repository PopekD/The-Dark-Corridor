#include "Raycast.h"

Raycast::Raycast(sf::RenderWindow& window)
{
    SCREEN_WIDTH = window.getSize().x;
    SCREEN_HEIGHT = window.getSize().y;
    lines = sf::VertexArray(sf::Lines, 2 * SCREEN_WIDTH);
    floorlines = sf::VertexArray(sf::Lines, 2 * SCREEN_WIDTH);
}

void Raycast::initializeTextures() {
    
    try
    {
        textures[2].loadFromFile("Assets/wall.png");
        textures[3].loadFromFile("Assets/window.jpg");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }


    desksprite = sf::Sprite(textures[4]);
    desksprite.setOrigin(sf::Vector2f(textures[4].getSize().x / 2 , 0));
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

            if (Minimap::Map[unsigned int(mapY / Minimap::cellSize.y)][unsigned int(mapX / Minimap::cellSize.x)] > 0) {
                hit = 1;
            }

        }


            double perpWallDist = 0.0;
            if (side == 0) {
                perpWallDist = (sideDistX - deltaDistX) / Minimap::cellSize.x;
            }
            else {
                perpWallDist = (sideDistY - deltaDistY) / Minimap::cellSize.y;
            }


        
            float lineHeight = SCREEN_HEIGHT / perpWallDist;
            int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawStart < 0) drawStart = 0;
            int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;


            int texNum = Minimap::Map[unsigned int(mapY / Minimap::cellSize.y)][unsigned int(mapX / Minimap::cellSize.x)] - 1;


            double wallX; //where exactly the wall was hit
            if (side == 0) wallX = (playerPos.y / Minimap::cellSize.y) + perpWallDist * rayDirY;
            else           wallX = (playerPos.x / Minimap::cellSize.x) + perpWallDist * rayDirX;
            wallX -= floor((wallX));

            //x coordinate on the texture
            int texX = int(wallX * double(wallSize));
            if (side == 0 && rayDirX > 0) texX = wallSize - texX - 1;
            if (side == 1 && rayDirY < 0) texX = wallSize - texX - 1;



            int floorHeight = (drawStart + drawEnd);

            floorlines.append(sf::Vertex(
                sf::Vector2f(i, drawEnd / 2), sf::Color(22, 22, 29, 0)
            ));
            floorlines.append(sf::Vertex(
                sf::Vector2f(i, floorHeight), sf::Color(255, 218, 121, 50)
            ));


            lines.append(sf::Vertex(
                sf::Vector2f(i, drawStart), sf::Color(22, 22, 29, 0),
                sf::Vector2f(texX, 0)
            ));
            lines.append(sf::Vertex(
                sf::Vector2f(i, drawEnd), sf::Color(22, 22, 29, 0),
                sf::Vector2f(texX, wallSize)
            ));



            double distance = sqrt(pow(mapX - playerPos.x, 2) + pow(mapY - playerPos.y, 2));
            if (distance <= maxRenderDistance) {
                double alpha = 255.0 * (maxRenderDistance - distance) / maxRenderDistance; // calculate alpha based on distance
                sf::Color color = sf::Color(255, 218, 121, static_cast<sf::Uint8>(alpha)); // create a color with the adjusted alpha value
                lines[0].color = color;
                lines[1].color = color;
                floorlines[0].color = color;
                floorlines[1].color = color;
            }
           
            window.draw(lines, &textures[texNum]);
            lines.clear();
    }
    window.draw(floorlines);
    floorlines.clear();
    
}


Raycast::~Raycast() {}