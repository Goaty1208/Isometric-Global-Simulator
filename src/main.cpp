#include "raylib.h"
#include <iostream>

const unsigned int windowHeight = 600;
const unsigned int windowWidth = 600;

//Conversion rates------------------------
const float i_x = 1.0f;
const float i_y = 0.5f;
const float j_x = -1.0f;
const float j_y = 0.5f;
//Tile heights and widths. Standard-------

//NOTE: These values should NOT change, regardless of any zooming factor

const int tileWidth = 32;       
const int tileHeight = 16;      

//----------------------------------------


Vector2 isometricToScreen(Vector2 isoPosition) {
    Vector2 screenPosition;
    screenPosition.x = (isoPosition.x - isoPosition.y) * (tileWidth * i_x);
    screenPosition.y = (isoPosition.x + isoPosition.y) * (tileHeight * i_y);
    return screenPosition;
}



int main(){

    InitWindow(windowWidth, windowHeight, "Et Erat Bellum - 0.0.0.0.0.0.0.1");

    Image grass = LoadImage("graphics/tiles/grass.png");
    Texture2D grassTexture = LoadTextureFromImage(grass);
    
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        BeginDrawing();

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++){
                Vector2 tilePosition = { static_cast<float>(i), static_cast<float>(j) };
                Vector2 screenPosition = isometricToScreen(tilePosition);
                DrawTexture(grassTexture, screenPosition.x, screenPosition.y, WHITE);
            }
        }

        DrawFPS(1,1);

        ClearBackground(BLACK);
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}

