#include <iostream>

#include "raylib.h"
#include "raymath.h"

#include "engine/mapGeneration.hpp"
#include "engine/mapArithmetics.hpp"
#include "engine/mapObject.hpp"
#include "engine/mouseInput.hpp"
#include "engine/human.hpp"

class ProgramState{

private:
    void windowResCheck();
    void cameraUpdate();
    void checkInput();
    void updateTime();
public:
    int frameCounter;
    Camera2D camera;
    double previousTime;    // Previous time measure
    double currentTime;           // Current time measure
    double updateDrawTime;        // Update + Draw time
    double waitTime;              // Wait time (if target fps required)
    float deltaTime;             // Frame time (Update + Draw + Wait time)  
    int targetFPS;

    void updateProgram();

    //Textures ---------------------
    //TODO: Texture atlas

    Texture2D grassTexture;
    Texture2D waterTexture;
    Texture2D humanDefault;
    
    //------------------------------
    
    ProgramState();
    ~ProgramState();
};

ProgramState::ProgramState(){

    this->frameCounter = 0;

    this->camera = { 0 };
    this->camera.zoom = 1.0f;

    InitWindow(windowWidth, windowHeight, "Isometric Global Simulator- 0.0.0.16");

    this->previousTime = GetTime();
    this->currentTime = 0.0;
    this->updateDrawTime = 0.0;
    this->waitTime = 0.0;
    this->deltaTime = 0.0f;
    this->targetFPS = 60;

    this->grassTexture = LoadTexture("graphics/tiles/grass.png");
    this->waterTexture = LoadTexture("graphics/tiles/water.png");
    this->humanDefault = LoadTexture("graphics/creatures/human.png");
}

ProgramState::~ProgramState(){
    // UnloadTexture(this->grassTexture);
    // UnloadTexture(this->waterTexture);
    // UnloadTexture(this->humanDefault);
}



void ProgramState::windowResCheck(){

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
        //Definetly original resolution code stops here -------------------------------------------------
 	}
}

void ProgramState::cameraUpdate(){

    //Camera shitfuckery starts ------------------------------------
    // Translate based on mouse right click
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / this->camera.zoom);

        this->camera.target = Vector2Add(this->camera.target, delta);
    }

    // Zoom based on mouse wheel
    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        // Get the world point that is under the mouse
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), this->camera);
        
        // Set the offset to where the mouse is
        this->camera.offset = GetMousePosition();

        // Set the target to match, so that the camera maps the world space point 
        // under the cursor to the screen space point under the cursor at any zoom
        this->camera.target = mouseWorldPos;

        // Zoom increment
        const float zoomIncrement = 0.125f;

        this->camera.zoom += (wheel*zoomIncrement);
        if (this->camera.zoom < zoomIncrement) this->camera.zoom = zoomIncrement;
        
    }
        //Camera ends --------------------------------------------------

}

void ProgramState::checkInput(){

    Vector2 screenPosition = screenToIsometricPrecise(GetScreenToWorld2D(GetMousePosition(), this->camera));
    Vector2 mousePos = GetMousePosition();

    std::cout << "Mouse X: " << screenPosition.x << " Mouse Y: " << screenPosition.y <<"\n";

}

void draw(ProgramState programState){



}

void ProgramState::updateTime(){

    this->currentTime = GetTime();
    this->updateDrawTime = this->currentTime - this->previousTime;
        
    if (this->targetFPS > 0)          // We want a fixed frame rate
    {
        this->waitTime = (1.0f/(float)this->targetFPS) - this->updateDrawTime;
        if (this->waitTime > 0.0) 
        {
            WaitTime((float)this->waitTime);
            this->currentTime = GetTime();
            this->deltaTime = (float)(this->currentTime - this->previousTime);
        }
    }
    else this->deltaTime = (float)this->updateDrawTime;    // Framerate could be variable

    this->previousTime = this->currentTime;
    this->frameCounter++;

}

void ProgramState::updateProgram(){

    this->windowResCheck();
    this->cameraUpdate();
    this->checkInput();
    this->updateTime();
}

class GameState{

private:
    ProgramState programState;
public:
    mapObject currentMap;
    std::vector<Human> human; //All humans have STDs
    GameState(int currentMapSize, ProgramState programState);
    ~GameState();
    void renderGame();
};

//Classes are funny
GameState::GameState(int currentMapSize, ProgramState programState) : currentMap(currentMapSize){

    this->programState = programState;

}

GameState::~GameState(){

}

void GameState::renderGame(){

    drawMap(this->programState.grassTexture, this->programState.waterTexture, this->currentMap.size, this->currentMap.mapArray, this->programState.camera);

}

void runGame(ProgramState programState, GameState gameState){ 

    SetTargetFPS(programState.targetFPS);

    while (!WindowShouldClose()){

        mouseUpdateOnClick(programState.camera, gameState.currentMap.mapArray, gameState.currentMap.size);

        programState.updateProgram();

        //Draw segment.
        BeginDrawing();

            ClearBackground(BLACK);
            BeginMode2D(programState.camera);

            gameState.renderGame();

            EndMode2D();

            DrawFPS(1,1);
   
        EndDrawing();

    }

    CloseWindow();
}

