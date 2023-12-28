#include "raylib.h"
#include <cmath>
#include <cassert>
#define assertm(exp, msg)

#ifndef PERLIN_HPP
#define PERLIN_HPP

//Perlin Noise Generator -----------------------------------------------------------------
Vector2 randomGradient(int ix, int iy);

float dotGridGradient(int ix, int iy, float x, float y);

float cubicInterpolation(float a0, float a1, float w);

float perlinGeneration(float x, float y);

#endif