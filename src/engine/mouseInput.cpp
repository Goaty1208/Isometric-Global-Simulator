#include "engine/mouseInput.hpp"

void mouseUpdateHeld(Camera2D camera, int** currentMap, int frameCounter, int frameCount, int size){

    if (frameCounter % frameCount == 0 && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 screenPosition = screenToIsometric(GetScreenToWorld2D(GetMousePosition(), camera));

        if (screenPosition.x > 0 && screenPosition.y > 0) {
            std::cout << "Left Mouse Button Pressed\n";
            updateMap(currentMap, screenPosition, mapDebug);
        } else if (screenPosition.x == 0 || screenPosition.y == 0) {
            std::cout << "Out of bounds!";
        }
    }
}

void mouseUpdateOnClick(Camera2D camera, int** currentMap, int size){

    Vector2 screenPosition = screenToIsometric(GetScreenToWorld2D(GetMousePosition(), camera));

    if (screenPosition.x > 0 && screenPosition.y > 0) {
        std::cout << "Left Mouse Button Pressed\n";
        updateMap(currentMap, screenPosition, mapDebug);
    }

}