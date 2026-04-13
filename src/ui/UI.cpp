#include "simulator/ui/UI.h"


UI::UI(Simulation* sim, SimulationConfig* cfg)
    : simulation(sim), config(cfg) {
}

void UI::Render() {
    RenderSimulationPanel();
}

void UI::RenderSimulationPanel() {
    // Collapsible panel
    if (ImGui::CollapsingHeader("Simulation Controls", ImGuiTreeNodeFlags_DefaultOpen)) {

        // Optional: make a scrollable child region for many controls
        ImGui::BeginChild("SimulationPanelChild", ImVec2(0, 200), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);

        // Simulation settings
        ImGui::SliderInt("Agents", &config->numAgents, 1, 500);
        ImGui::SliderFloat("Velocity", &config->velocity, 0.0f, 10.0f);

        // Action buttons
        if (ImGui::Button("Restart")) {
            // simulation->Reset(*config);
        }

        // You can add more controls here, and the scroll bar will appear if needed
        ImGui::Text("Additional controls can go here...");
        ImGui::Text("Panel expands as needed.");

        ImGui::EndChild(); // End scrollable region
    }
}