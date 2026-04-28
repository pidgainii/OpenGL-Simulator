#include "simulator/ui/UI.h"
#include "imgui.h"

UI::UI(Simulation* sim)
    : simulation(sim), showFullMenu(true) {
}

void UI::Render(int& selectedIdx, bool& isSimulating, const std::vector<std::unique_ptr<Engine>>& engines) {
    // We call the selector which handles the 3 states (Running, Paused-Mini, Dashboard)
    RenderScenarioSelector(selectedIdx, isSimulating);
}

void UI::RenderScenarioSelector(int& selectedIdx, bool& isSimulating) {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    float padding = 20.0f;

    // --- STATE 1: Simulation is RUNNING (Clean Screen) ---
    if (isSimulating) {
        ImVec2 windowPos = ImVec2(viewport->WorkPos.x + viewport->WorkSize.x - padding, viewport->WorkPos.y + padding);
        ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, ImVec2(1.0f, 0.0f));
        ImGui::SetNextWindowBgAlpha(0.0f);

        if (ImGui::Begin("SimInfo", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs)) {
            ImGui::TextColored(ImVec4(1, 1, 1, 0.5f), "Press [P] to Pause");
        }
        ImGui::End();

        showFullMenu = false; // Ensure state is reset
        return;
    }

    // --- STATE 2: Simulation is PAUSED (But Menu is Hidden) ---
    if (!isSimulating && !showFullMenu) {
        ImVec2 windowPos = ImVec2(viewport->WorkPos.x + viewport->WorkSize.x - padding, viewport->WorkPos.y + padding);
        ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, ImVec2(1.0f, 0.0f));

        if (ImGui::Begin("PausedButton", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove)) {
            ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "PAUSED");
            ImGui::Separator();
            if (ImGui::Button("OPEN DASHBOARD", ImVec2(140, 45))) {
                showFullMenu = true;
            }
        }
        ImGui::End();
        return;
    }

    // --- STATE 3: FULL DASHBOARD (The big configuration panel) ---
    ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(800, 500), ImGuiCond_Always);

    ImGui::Begin("Scenario Manager", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowFontScale(1.2f);

    ImGui::Text("Simulation Control Center");
    ImGui::Separator();
    ImGui::Spacing();

    // --- SECTION: PROPULSION SELECTION ---
    ImGui::Text("1. Select Propulsion Model:");
    const char* engineNames[] = { "Holonomic Model", "Ackermann Steering", "Unicycle Model" };
    ImGui::PushItemWidth(-1);
    ImGui::Combo("##EngineCombo", &selectedIdx, engineNames, IM_ARRAYSIZE(engineNames));
    ImGui::PopItemWidth();

    ImGui::Spacing();

    // --- SECTION: CONFIGURATION & DESCRIPTION ---
    // We use two columns inside the dashboard to show Description and Config side-by-side
    ImGui::Columns(2, "DashColumns", false);
    ImGui::SetColumnWidth(0, 450);

    ImGui::Text("Model Description:");
    ImGui::BeginChild("DescChild", ImVec2(0, 180), true);
    ImGui::TextWrapped("Currently Selected: %s", engineNames[selectedIdx]);
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::TextWrapped("This model handles the mathematical constraints of agent movement. "
        "Ensure the environment scale matches the propulsion dynamics.");
    ImGui::EndChild();

    ImGui::NextColumn();

    ImGui::Text("Live Configuration:");
    ImGui::BeginChild("ConfigChild", ImVec2(0, 180), true);

    // Move the "Simulation Panel" logic directly inside the Dashboard
    ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "System Status: STANDBY");
    ImGui::Separator();

    static float simSpeed = 1.0f;
    ImGui::SliderFloat("Speed", &simSpeed, 0.1f, 5.0f);

    if (ImGui::Button("Reset Scene Positions", ImVec2(-1, 35))) {
        // Reset logic here
    }

    ImGui::EndChild();

    ImGui::Columns(1);

    // --- SECTION: ACTION BUTTONS ---
    float buttonHeight = 70.0f;
    ImGui::SetCursorPosY(ImGui::GetWindowHeight() - (buttonHeight + 20.0f));

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.5f, 0.15f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));

    if (ImGui::Button("INICIAR SIMULACION", ImVec2(-1, buttonHeight))) {
        isSimulating = true;
        showFullMenu = false;
    }

    ImGui::PopStyleColor(2);
    ImGui::End();
}

// RenderSimulationPanel is no longer called separately in Render() 
// because its contents are now integrated into the State 3 Dashboard.
void UI::RenderSimulationPanel(bool isSimulating) {
    // Keep empty or remove if you prefer the integrated dashboard approach
}