#pragma once

#include "imgui.h"

// Forward declarations (avoid heavy includes)
class Simulation;

struct SimulationConfig {
    int numAgents = 50;
    float velocity = 1.0f;
};

class UI {
public:
    UI(Simulation* sim, SimulationConfig* config);

    // Called every frame between NewFrame() and Render()
    void Render();

private:
    void RenderSimulationPanel();

private:
    Simulation* simulation;
    SimulationConfig* config;
};