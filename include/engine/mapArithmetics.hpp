#include "raylib.h"

#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "perlin.hpp"

#ifndef MAP_ARITHMETICS_HPP
#define MAP_ARITHMETICS_HPP

//Resolution thingies---------------------
const unsigned int windowHeight = 600;
const unsigned int windowWidth = 600;
extern int display;
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
const int mapDebug = 16;
const int mapSize = 256;
const int mapSizeMedium = 1024;
const int mapSizeLarge = 2048;
const int mapSizeExtra = 4096;
//----------------------------------------

enum tileIDs{
    
    water = 0,
    grass = 1

};

//Isometric coordinate to screen converter for tiles.
Vector2 isometricToScreenTiles(Vector3 isoPosition);

//Isometric coordinate converter.
Vector2 isometricToScreen(Vector3 isoPosition);

//Screen coordinate to isometric converter for tiles.
Vector2 screenToIsometric(Vector2 screenPosition);

void drawMap(Texture2D grassTexture, Texture2D waterTexture, int drawSize, int** map);

void updateMap(int** map, Vector2 position, int mapSize);


// Check for left mouse button press every frameCount frames, then update the map
void mouseUpdate(Camera2D camera, int** currentMap, int frameCounter, int frameCount);

#endif