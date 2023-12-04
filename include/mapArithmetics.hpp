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
const int mapDebug = 64;
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

#endif