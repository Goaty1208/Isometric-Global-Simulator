#include "raylib.h"
#include "raymath.h"

#include "mapGeneration.hpp"
#include "mapArithmetics.hpp"
#include "mapObject.hpp"

int frameCounter = 0;

int main(){
    
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    InitWindow(windowWidth, windowHeight, "Isometric Global Simulator- 0.0.0.0.0.0.0.11");

    Image grass = LoadImage("graphics/tiles/grass.png");
    Texture2D grassTexture = LoadTextureFromImage(grass);
    Image water = LoadImage("graphics/tiles/water.png");
    Texture2D waterTexture = LoadTextureFromImage(water);
    

    mapObject currentMap(mapSize);
    
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
            delta = Vector2Scale(delta, -1.0f / camera.zoom);

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
        Vector2 screenPosition = screenToIsometric(GetScreenToWorld2D(GetMousePosition(), camera));
        Vector2 mousePos = GetMousePosition();
        Vector2 screenPos = GetScreenToWorld2D(mousePos, camera);
        Vector2 isoPos = screenToIsometric(screenPos);

        frameCounter++;

        mouseUpdate(camera, currentMap.mapValues, frameCounter, 5);

        //Draw segment.
        BeginDrawing();

            ClearBackground(BLACK);
            BeginMode2D(camera);
            
            drawMap(grassTexture, waterTexture, currentMap.size, currentMap.mapValues);

            EndMode2D();

            DrawFPS(1,1);
   
        EndDrawing();

    }

    UnloadTexture(grassTexture);
    UnloadImage(grass);
    UnloadTexture(waterTexture);
    UnloadImage(water);

    CloseWindow();

    return 0;
}