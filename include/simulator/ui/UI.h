#pragma once
#include <vector>
#include <memory>
#include "simulator/core/Engine.h"

// Forward declarations
class Simulation;

class UI {
public:
    UI(Simulation* sim);

    // Main render loop
    void Render(int& selectedIdx, bool& isSimulating, const std::vector<std::unique_ptr<Engine>>& engines);

private:
    void RenderScenarioSelector(int& selectedIdx, bool& isSimulating);
    void RenderSimulationPanel(bool isSimulating);

    Simulation* simulation;

    // --- NEW STATE VARIABLE ---
    // Tracks if we are showing the large configuration menu 
    // or the tiny "contracted" pause button.
    bool showFullMenu;
};