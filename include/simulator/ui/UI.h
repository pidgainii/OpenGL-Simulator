#pragma once
#include <vector>
#include <memory>
#include "simulator/core/Engine.h"

// Forward declarations
class Simulation;

class UI {
public:
    UI(Simulation* sim);

    void Render(int& selectedIdx, bool& isSimulating, const std::vector<std::unique_ptr<Engine>>& engines, int& numAgents, int& selectedModel, int& selectedTraj, bool& triggerReset);
    void RenderScenarioSelector(int& selectedIdx, bool& isSimulating, int& numAgents, int& selectedModel, int& selectedTraj, bool& triggerReset);

private:
    void RenderScenarioSelector(int& selectedIdx, bool& isSimulating);
    void RenderSimulationPanel(bool isSimulating);

    Simulation* simulation;

    bool showFullMenu;
};