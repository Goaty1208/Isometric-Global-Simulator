#include "raylib.h"
#include "raymath.h"

#include "mapGeneration.hpp"
#include "mapArithmetics.hpp"


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

//What in the C++ is this shit -----------------------
int** generateMap(int mapSize) {

    srand(static_cast<unsigned int>(time(nullptr)));

    float offsetX = static_cast<float>(rand()) / RAND_MAX * 1000.0f;
    float offsetY = static_cast<float>(rand()) / RAND_MAX * 1000.0f;
    float scale = static_cast<float>(rand()) / RAND_MAX * 8.0f;

    Image perlinNoise = GenImagePerlinNoise(mapDebug, mapDebug, offsetX, offsetY, scale);

    int** map = new int*[mapSize];

    for (int i = 0; i < mapSize; ++i) {

        map[i] = new int[mapSize];

        for (int j = 0; j < mapSize; ++j) {

            //Funky magic shite
            Color pixelColor = GetImageColor(perlinNoise, i, j);

            // Normalize the color values to a range suitable for your tile IDs
            float normalizedValue = (pixelColor.r + pixelColor.g + pixelColor.b) / (3.0f * 255.0f);
            std::cout << "Normalized Value at (" << i << ", " << j << "): " << normalizedValue << std::endl;

            // Assign grass or water based on a threshold
            map[i][j] = (normalizedValue < 0.5f) ? grass : water;
        }
    }

        UnloadImage(perlinNoise);

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

    InitWindow(windowWidth, windowHeight, "Isometric Global Simulator- 0.0.0.0.0.0.0.8");

    Image grass = LoadImage("graphics/tiles/grass.png");
    Texture2D grassTexture = LoadTextureFromImage(grass);
    Image water = LoadImage("graphics/tiles/water.png");
    Texture2D waterTexture = LoadTextureFromImage(water);
    

    int** currentMap = new int*[mapSize];

    currentMap = generateMap(mapDebug);
    
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
            
            drawMap(grassTexture, waterTexture, mapDebug, currentMap);

            EndMode2D();

            DrawFPS(1,1);
   
        EndDrawing();

    }
    
    delete2DIntArray(currentMap, mapDebug);
    UnloadTexture(grassTexture);
    UnloadImage(grass);
    UnloadTexture(waterTexture);
    UnloadImage(water);

    CloseWindow();

    return 0;
}