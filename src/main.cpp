#include "raylib.h"

const unsigned int windowHeight = 600;
const unsigned int windowWidth = 600;


int main(){

    InitWindow(windowWidth, windowHeight, "Et Erat Bellum");

    Image grass = LoadImage("graphics/tiles/grass.png");
    Texture2D grass = LoadTextureFromImage(grass);


    while (!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(BLACK);
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}
