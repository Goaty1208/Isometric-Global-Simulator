#include "raylib.h"
#include "raymath.h"

#include <thread>
#include <iostream>

#include "engine/mapGeneration.hpp"
#include "engine/mapArithmetics.hpp"
#include "engine/mapObject.hpp"
#include "engine/mouseInput.hpp"
#include "engine/human.hpp"

int frameCounter = 0;

int main(){
    
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    InitWindow(windowWidth, windowHeight, "Isometric Global Simulator- 0.0.0.15");

    double previousTime = GetTime();    // Previous time measure
    double currentTime = 0.0;           // Current time measure
    double updateDrawTime = 0.0;        // Update + Draw time
    double waitTime = 0.0;              // Wait time (if target fps required)
    float deltaTime = 0.0f;             // Frame time (Update + Draw + Wait time)  
    int targetFPS = 60;


    Texture2D grassTexture = LoadTexture("graphics/tiles/grass.png");
    Texture2D waterTexture = LoadTexture("graphics/tiles/water.png");
    Texture2D humanDefault = LoadTexture("graphics/creatures/human.png");
    

    mapObject currentMap(mapSizeMedium);
    
    Human jerry(humanDefault, {0, 0, 0});

    SetTargetFPS(targetFPS);

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

        std::cout << "Mouse X: " << isoPos.x << " Mouse Y: " << isoPos.y <<"\n";

        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
        {
            jerry.setPosition(isoPos.x, isoPos.y);

        }

        frameCounter++;

        //std::cout << "Mouse X: " << mousePosIso.x << " Mouse Y: " << mousePosIso.y << "\n";

        mouseUpdateOnClick(camera, currentMap.mapArray, currentMap.size);

        jerry.update();

        //Draw segment.
        BeginDrawing();

            ClearBackground(BLACK);
            BeginMode2D(camera);
            
            drawMap(grassTexture, waterTexture, currentMap.size, currentMap.mapArray, camera);

            jerry.render(camera);

            EndMode2D();

            DrawFPS(1,1);
   
        EndDrawing();


        currentTime = GetTime();
        updateDrawTime = currentTime - previousTime;
        
        if (targetFPS > 0)          // We want a fixed frame rate
        {
            waitTime = (1.0f/(float)targetFPS) - updateDrawTime;
            if (waitTime > 0.0) 
            {
                WaitTime((float)waitTime);
                currentTime = GetTime();
                deltaTime = (float)(currentTime - previousTime);
            }
        }
        else deltaTime = (float)updateDrawTime;    // Framerate could be variable

        previousTime = currentTime;

    }

    UnloadTexture(grassTexture);
    UnloadTexture(waterTexture);
    UnloadTexture(humanDefault);

    CloseWindow();

    return 0;
}

