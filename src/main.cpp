#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>

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
const int mapDebug = 10;
const int mapSize = 256;
const int mapSizeMedium = 1024;
const int mapSizeLarge = 2048;
const int mapSizeExtra = 4096;
//----------------------------------------


enum tileIDs{
    
    water = 0,
    grass = 1

};



int mapTiles[mapDebug][mapDebug]{
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

void drawMap(Texture2D grassTexture, Texture2D waterTexture, int drawSize){
    for (int i = 0; i < drawSize; i++) { //Tile drawing. Pretty damn primitive
        for (int j = 0; j < drawSize; j++) {
            Vector2 tilePosition = { static_cast<float>(i), static_cast<float>(j) };
            Vector2 screenPosition = isometricToScreenTiles(tilePosition);
            switch (mapTiles[i][j])
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

//What in the C++ is this shit -----------------------
int** generateMap(int mapSize, Image perlinMap) {

    int** map = new int*[mapSize];

    for (int i = 0; i < mapSize; ++i) {

        map[i] = new int[mapSize];

        for (int j = 0; j < mapSize; ++j) {

            //Funky magic shite
            map[i][j] = ColorToInt(GetImageColor(perlinMap, i, j));
        }
    }



    return map;
}

//I like memory leaks. Note: this function must use the same map size as the size of the map it wants to delete, as otherwise things might very well explode.
void delete2DIntArray(int** map, int mapSize) {
    for (int i = 0; i < mapSize; ++i) {

        delete[] map[i];
    }

    delete[] map;
}

//----------------------------------------------------

int main(){
    
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    InitWindow(windowWidth, windowHeight, "Et Erat Bellum - 0.0.0.0.0.0.0.6");

    Image grass = LoadImage("graphics/tiles/grass.png");
    Texture2D grassTexture = LoadTextureFromImage(grass);
    Image water = LoadImage("graphics/tiles/water.png");
    Texture2D waterTexture = LoadTextureFromImage(water);
    Image perlinNoise = GenImagePerlinNoise(mapDebug, mapDebug, 1, 1, 1.0f);
    
    SetTargetFPS(60);

    while (!WindowShouldClose()){

        //Window resolution checking. ------------------------------------------------------------------
        if ((IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))))
 		{
            // see what display we are on right now
 			int display = GetCurrentMonitor();
 
            
            if (IsWindowFullscreen())
            {
                // if we are full screen, then go back to the windowed size
                SetWindowSize(windowWidth, windowHeight);
            }
            else
            {
                // if we are not full screen, set the window size to match the monitor we are on
                SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
            }
 
            // toggle the state
 			ToggleFullscreen();
 		}
        //Definetly original resolution code stops here -------------------------------------------------

        //Camera shitfuckery starts ------------------------------------
        // Translate based on mouse right click
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);

            camera.target = Vector2Add(camera.target, delta);
        }

        // Zoom based on mouse wheel
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            
            // Set the offset to where the mouse is
            camera.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point 
            // under the cursor to the screen space point under the cursor at any zoom
            camera.target = mouseWorldPos;

            // Zoom increment
            const float zoomIncrement = 0.125f;

            camera.zoom += (wheel*zoomIncrement);
            if (camera.zoom < zoomIncrement) camera.zoom = zoomIncrement;
        }
        //Camera ends --------------------------------------------------

        //Draw segment.
        BeginDrawing();

            ClearBackground(BLACK);
            BeginMode2D(camera);
            
            drawMap(grassTexture, waterTexture, mapDebug);

            EndMode2D();

            DrawFPS(1,1);
   
        EndDrawing();

    }
    
    UnloadTexture(grassTexture);
    UnloadImage(grass);
    UnloadTexture(waterTexture);
    UnloadImage(water);

    UnloadImage(perlinNoise);

    CloseWindow();

    return 0;
}