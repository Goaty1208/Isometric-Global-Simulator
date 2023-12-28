#include "engine/perlin.hpp"

Vector2 randomGradient(int ix, int iy) {
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443;

    b ^= a << s | a >> (w - s);
    b *= 1911520717;

    a ^= b << s | b >> (w - s);
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]

    // Create the vector from the angle
    Vector2 v;
    v.x = std::sin(random);
    v.y = std::cos(random);

    return v;
}

float dotGridGradient(int ix, int iy, float x, float y) {
    assertm(ix >= 0 && iy >= 0, "Gradient Error"); // Ensure non-negative indices
    Vector2 gradient = randomGradient(ix, iy);

    float dx = x - static_cast<float>(ix);
    float dy = y - static_cast<float>(iy);

    return (dx * gradient.x + dy * gradient.y);
}


float cubicInterpolation(float a0, float a1, float w) {
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

float perlinGeneration(float x, float y) {
    int x0 = static_cast<int>(x);
    int y0 = static_cast<int>(y);
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    // Interpolation weights
    float sx = x - static_cast<float>(x0);
    float sy = y - static_cast<float>(y0);

    // Interpolate top
    float n0 = dotGridGradient(x0, y0, x, y);
    float n1 = dotGridGradient(x1, y0, x, y);
    float ix0 = cubicInterpolation(n0, n1, sx);

    // Interpolate bottom
    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    float ix1 = cubicInterpolation(n0, n1, sx);

    // Interpolate top and bottom
    return (cubicInterpolation(ix0, ix1, sy) + 1.0f) / 2.0f;
}