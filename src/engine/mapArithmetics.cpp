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

void drawMap(Texture2D grassTexture, Texture2D waterTexture, int drawSize, int** map){

    for (int i = 0; i < drawSize; i++) { //Tile drawing. Pretty damn primitive
        for (int j = 0; j < drawSize; j++) {
            Vector3 tilePosition = { static_cast<float>(i), static_cast<float>(j), static_cast<float>(map[i][j]) };
            Vector2 screenPosition = isometricToScreenTiles(tilePosition);
            switch (map[i][j])
            {
            case grass:
                DrawTexture(grassTexture, screenPosition.x, screenPosition.y, WHITE);
                break;
            
            case water:
                DrawTexture(waterTexture, screenPosition.x, screenPosition.y, WHITE);
                break;
            default:
                DrawTexture(waterTexture, screenPosition.x, screenPosition.y, WHITE);
                break;
            }
                        
        }
    }    

}

void updateMap(int** map, Vector2 position, int mapSize){
    int x = static_cast<int>(position.x) - 1;
    int y = static_cast<int>(position.y) - 1;

    // Check if the coordinates are within bounds before using them as indices
    if (x >= 0 && x < mapSize && y >= 0 && y < mapSize) {
        // Update map at the rounded coordinates
        std::cout << "Before Update - map[" << x << "][" << y << "] = " << map[x][y] << "\n";
        switch (map[x][y]){
        
        case 1:
            map[x][y] = 0;
            break;
        case 0:
            map[x][y] = 1;
            break;
        }
        std::cout << "After Update - map[" << x << "][" << y << "] = " << map[x][y] << "\n";
    }
}
