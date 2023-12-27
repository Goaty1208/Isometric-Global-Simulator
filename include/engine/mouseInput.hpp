#include "raylib.h"
#include "mapArithmetics.hpp"

#ifndef MOUSE_INPUT_HPP
#define MOUSE_INPUT_HPP

void mouseUpdateHeld(Camera2D camera, int* currentMap, int frameCounter, int frameCount, int size);

void mouseUpdateOnClick(Camera2D camera, int* currentMap, int size);
#endif