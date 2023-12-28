#include "engine/mapArithmetics.hpp"

int display = GetCurrentMonitor();

Vector2 isometricToScreenTiles(Vector3 isoPosition) {
    Vector2 screenPosition;
    screenPosition.x = (isoPosition.x - isoPosition.y) * (tileWidth * i_y);
    screenPosition.y = (isoPosition.x + isoPosition.y) * (tileHeight * j_y);
    return screenPosition;
}

Vector2 isometricToScreen(Vector3 isoPosition) {
    Vector2 screenPosition;
    screenPosition.x = (isoPosition.x - isoPosition.y) * (tileWidth * i_y);
    screenPosition.y = (isoPosition.x + isoPosition.y) * (tileHeight * j_y);
    return screenPosition;
}

Vector2 screenToIsometric(Vector2 screenPosition) {
    Vector2 isoPosition;
    isoPosition.x = (screenPosition.x / (tileWidth * 0.5f) + screenPosition.y / (tileHeight * 0.5f)) * 0.5f;
    isoPosition.y = (screenPosition.y / (tileHeight * 0.5f) - (screenPosition.x / (tileWidth * 0.5f))) * 0.5f;
    
    // Round to the nearest whole values
    isoPosition.x = static_cast<float>(std::round(isoPosition.x));
    isoPosition.y = static_cast<float>(std::round(isoPosition.y) + 1);

    return isoPosition;
}

//Might work. I hope. Update: broke fucking everything
int index2Dto1D(int i, int j, int size){

    return i*size+j;

}

void drawMap(Texture2D grassTexture, Texture2D waterTexture, int drawSize, int* map, Camera2D camera){

    Vector2 screenSize = { static_cast<float>(windowWidth), static_cast<float>(windowHeight) };
    Vector2 worldSize = GetScreenToWorld2D(screenSize, camera);
    
    for (int i = 0; i < drawSize; i++) { //Tile drawing. Pretty damn primitive
        for (int j = 0; j < drawSize; j++) {

            Vector3 tilePosition = { static_cast<float>(i), static_cast<float>(j), static_cast<float>(map[index2Dto1D(i, j, drawSize)]) };
            Vector2 screenPosition = isometricToScreenTiles(tilePosition);
            
            Texture2D tile;
            
            switch (map[index2Dto1D(i, j, drawSize)])
            {
            case grass:
                tile = grassTexture;
                break;
            case water:
                tile = waterTexture;
                break;
            default:
                tile = waterTexture;
                break;
            }

            if ((screenPosition.x >= 0 && screenPosition.x <= worldSize.x && screenPosition.y >= 0 && screenPosition.y <= worldSize.y)){

                DrawTexture(tile, screenPosition.x, screenPosition.y, WHITE);

            }
                      
        }
    }    

}

void updateMap(int* map, Vector2 position, int mapSize){
    int x = static_cast<int>(position.x) - 1;
    int y = static_cast<int>(position.y) - 1;

    // Check if the coordinates are within bounds before using them as indices
    if (x >= 0 && x < mapSize && y >= 0 && y < mapSize) {
        // Update map at the rounded coordinates
        std::cout << "Before Update - map[" << x << "][" << y << "] = " << map[index2Dto1D(x, y, mapSize)] << "\n";
        switch (map[index2Dto1D(x, y, mapSize)]){
        
        case 1:
            map[index2Dto1D(x, y, mapSize)] = 0;
            break;
        case 0:
            map[index2Dto1D(x, y, mapSize)] = 1;
            break;
        }
        std::cout << "After Update - map[" << x << "][" << y << "] = " << map[index2Dto1D(x, y, mapSize)] << "\n";
    }
}