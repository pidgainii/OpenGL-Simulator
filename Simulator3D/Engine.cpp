#include "Engine.h"
#include <cmath>
#include <vector>
#include <algorithm>


static float r = 10.0f;
static float v = 0.5f;
static float L = 10.0f;

// GVF function
float gvf(float x, float y, float r, float k = 0.2f) {
    float tx = -2 * y;
    float ty = 2 * x;

    float phi = x * x + y * y - r * r;

    float nx = -k * phi * (2 * x);
    float ny = -k * phi * (2 * y);

    float Vx = tx + nx;
    float Vy = ty + ny;

    return atan2(Vy, Vx);
}

Engine::Engine() {
    x = 2.0f;
    y = 0.0f;
    z = 0.0f;
    theta = 0.0f;
}

void Engine::Init() {}

std::vector<float> Engine::UpdateSim(float dt) {

    // Desired angle
    float theta_d = gvf(x, y, r);

    // Shortest angle difference
    float error_theta = atan2(sin(theta_d - theta), cos(theta_d - theta));

    // Steering limit
    float phi = std::clamp(error_theta, -3.14159f / 4.0f, 3.14159f / 4.0f);

    // Ackermann model
    x += v * cos(theta) * dt;
    y += v * sin(theta) * dt;
    theta += (v / L) * tan(phi) * dt;

    return { y, 0, x, theta };
}