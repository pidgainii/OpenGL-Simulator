// UI.h
#pragma once
#include <vector>
#include <memory>
#include "simulator/core/Engine.h"

// Forward declarations
class Simulation;
struct SimulationConfig;

class UI {
public:
    UI(Simulation* sim);

    // Ahora recibe referencias de Application
    void Render(int& selectedIdx, bool& isSimulating, const std::vector<std::unique_ptr<Engine>>& engines);

private:
    void RenderScenarioSelector(int& selectedIdx, bool& isSimulating);
    void RenderSimulationPanel(bool isSimulating);

    Simulation* simulation;
};