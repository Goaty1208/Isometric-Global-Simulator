#include <iostream>
#include <algorithm>

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
    void updateTime();
public:
    int frameCounter;
    
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
    this->updateTime();
}

class GameState{

private:
    Vector2 screenSize = { static_cast<float>(windowWidth), static_cast<float>(windowHeight) };
    Vector2 worldSize = GetScreenToWorld2D(screenSize, this->camera);
    Vector2 screenZero = GetScreenToWorld2D({0.0f, 0.0f}, this->camera);
public:
    void checkInput();
    void cameraUpdate();
    Camera2D camera = { 0 };
    ProgramState programState;
    mapObject currentMap;
    std::vector<Human> human; //All humans have STDs
    GameState(int currentMapSize, ProgramState programState);
    ~GameState();
    void renderGame();
    void updateGame();
};

void GameState::checkInput(){

    Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), this->camera);
    mousePos.x -= tileWidth / 2;
    mousePos = screenToIsometricPrecise(mousePos);

    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)){

        this->human.push_back(Human(programState.humanDefault, {static_cast<float>(mousePos.x),static_cast<float>(mousePos.y),0}));

        std::cout << "X: " << mousePos.x << " Y: " << mousePos.y << "\n";
    }

   

}

//Classes are funny
GameState::GameState(int currentMapSize, ProgramState programState) : currentMap(currentMapSize){
    
    this->camera.zoom = 1.0f;
    this->programState = programState;

    human.push_back(Human(programState.humanDefault, {static_cast<float>(0),static_cast<float>(0),0}));


}

GameState::~GameState(){

}

void GameState::updateGame(){
   this->screenSize = { static_cast<float>(windowWidth), static_cast<float>(windowHeight) };
   this->worldSize = GetScreenToWorld2D(screenSize, this->camera);
   this->screenZero = GetScreenToWorld2D({0.0f, 0.0f}, this->camera);
}

bool compareHumans(const Human &a, const Human &b) {
    // Compare based on x and y coordinates
    if (a.position.y == b.position.y) {
        return a.position.x < b.position.x;
    }
    return a.position.y < b.position.y;
}


void GameState::renderGame(){
    
    drawMap(this->programState.grassTexture, this->programState.waterTexture, this->currentMap.size, this->currentMap.mapArray, this->camera);

    std::sort(this->human.begin(), this->human.end(), compareHumans); //Shit implementation

    for (Human &i : this->human){ //Human
        i.render(this->camera, this->screenZero, this->worldSize);
    }

}

void GameState::cameraUpdate(){

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

void runGame(ProgramState programState, GameState gameState){ 

    SetTargetFPS(programState.targetFPS);

    while (!WindowShouldClose()){

        mouseUpdateOnClick(gameState.camera, gameState.currentMap.mapArray, gameState.currentMap.size);

        programState.updateProgram();
        gameState.updateGame();
        
        gameState.cameraUpdate();
        gameState.checkInput();
        //Draw segment.
        BeginDrawing();

            ClearBackground(BLACK);
            BeginMode2D(gameState.camera);

            gameState.renderGame();

            EndMode2D();

            DrawFPS(1,1);
   
        EndDrawing();

    }

    CloseWindow();
}

