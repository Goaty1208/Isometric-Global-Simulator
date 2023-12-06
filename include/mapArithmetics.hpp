#include "raylib.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#ifndef MAP_ARITHMETICS_HPP
#define MAP_ARITHMETICS_HPP

//Resolution thingies---------------------
const unsigned int windowHeight = 600;
const unsigned int windowWidth = 600;
int display = GetCurrentMonitor();
//----------------------------------------

//Conversion rates------------------------
const float i_y = 0.5f;
const float j_y = 0.5f;
//Tile heights and widths. Standard-------


//NOTE: These values should NOT change, regardless of any zooming factor

const int tileWidth = 64;       
const int tileHeight = 32;      

//----------------------------------------

//Map sizes ------------------------------
const int mapDebug = 256;
const int mapSize = 256;
const int mapSizeMedium = 1024;
const int mapSizeLarge = 2048;
const int mapSizeExtra = 4096;
//----------------------------------------

enum tileIDs{
    
    water = 0,
    grass = 1

};

int mapDebugTiles[mapDebug][mapDebug]{
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,0,1,1,0,1,0},
    {0,1,1,1,0,0,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,0,0,0,0},
    {0,0,1,1,1,1,0,0,0,0},
    {0,0,0,1,0,1,1,0,0,0},
    {0,0,0,1,0,0,1,0,0,0},
    {0,0,0,0,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0}
} ;


//Isometric coordinate to screen converter for tiles.
Vector2 isometricToScreenTiles(Vector2 isoPosition) {
    Vector2 screenPosition;
    screenPosition.x = (isoPosition.x - isoPosition.y) * (tileWidth * i_y);
    screenPosition.y = (isoPosition.x + isoPosition.y) * (tileHeight * j_y);
    return screenPosition;
}

//Isometric coordinate converter.
Vector2 isometricToScreen(Vector2 isoPosition) {
    Vector2 screenPosition;
    screenPosition.x = (isoPosition.x - isoPosition.y) * (tileWidth * i_y);
    screenPosition.y = (isoPosition.x + isoPosition.y) * (tileHeight * j_y);
    return screenPosition;
}

//Screen coordinate to isometric converter for tiles.
//TODO: Implement. Yeah, this shit doesn't work yet.
Vector2 screenToIsometricTiles(Vector2 isoPosition) {
    Vector2 screenPosition;
    screenPosition.x = (isoPosition.x - isoPosition.y) * (tileWidth * i_y);
    screenPosition.y = (isoPosition.x + isoPosition.y) * (tileHeight * j_y);
    return screenPosition;
}

void drawMap(Texture2D grassTexture, Texture2D waterTexture, int drawSize, int** map){
    for (int i = 0; i < drawSize; i++) { //Tile drawing. Pretty damn primitive
        for (int j = 0; j < drawSize; j++) {
            Vector2 tilePosition = { static_cast<float>(i), static_cast<float>(j) };
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

//Perlin Noise Generator -----------------------------------------------------------------
Vector2 randomGradient(int ix, int iy) {
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443;

    b ^= a << s | a >> w - s;
    b *= 1911520717;

    a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]

    // Create the vector from the angle
    Vector2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}

float dotGridGradient(int ix, int iy, float x, float y) {
    Vector2 gradient = randomGradient(ix, iy);

    float dx = x - static_cast<float>(ix);
    float dy = y - static_cast<float>(iy);

    return (dx * gradient.x + dy * gradient.y);
}

float cubicInterpolation(float a0, float a1, float w) {
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

float perlinGeneration(float x, float y) {
    int x0 = static_cast<int>(x);
    int y0 = static_cast<int>(y);
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    // Interpolation weights
    float sx = x - static_cast<float>(x0);
    float sy = y - static_cast<float>(y0);

    // Interpolate top
    float n0 = dotGridGradient(x0, y0, x, y);
    float n1 = dotGridGradient(x1, y0, x, y);
    float ix0 = cubicInterpolation(n0, n1, sx);

    // Interpolate bottom
    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    float ix1 = cubicInterpolation(n0, n1, sx);

    // Interpolate top and bottom
    return (cubicInterpolation(ix0, ix1, sy) + 1.0f) / 2.0f;
}

#endif