#include "simulator/ui/UI.h"
#include "imgui.h"

UI::UI(Simulation* sim)
    : simulation(sim), showFullMenu(true) {
}

void UI::Render(
    int& selectedIdx,
    bool& isSimulating,
    const std::vector<std::unique_ptr<Engine>>& engines,
    int& numAgents,
    int& selectedModel,
    int& selectedTraj,
    bool& triggerReset
) {
    RenderScenarioSelector(
        selectedIdx,
        isSimulating,
        numAgents,
        selectedModel,
        selectedTraj,
        triggerReset
    );
}

void UI::RenderScenarioSelector(
    int& selectedIdx,
    bool& isSimulating,
    int& numAgents,
    int& selectedModel,
    int& selectedTraj,
    bool& triggerReset
) {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    float padding = 20.0f;

    // =========================================================
    // STATE 1: SIMULATION RUNNING
    // =========================================================
    if (isSimulating) {

        ImVec2 windowPos = ImVec2(
            viewport->WorkPos.x + viewport->WorkSize.x - padding,
            viewport->WorkPos.y + padding
        );

        ImGui::SetNextWindowPos(
            windowPos,
            ImGuiCond_Always,
            ImVec2(1.0f, 0.0f)
        );

        ImGui::SetNextWindowBgAlpha(0.0f);

        if (ImGui::Begin(
            "SimInfo",
            nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoInputs
        )) {
            ImGui::TextColored(
                ImVec4(1, 1, 1, 0.5f),
                "Press [P] to Pause"
            );
        }

        ImGui::End();

        showFullMenu = false;
        return;
    }

    // =========================================================
    // STATE 2: PAUSED
    // =========================================================
    if (!isSimulating && !showFullMenu) {

        ImVec2 windowPos = ImVec2(
            viewport->WorkPos.x + viewport->WorkSize.x - padding,
            viewport->WorkPos.y + padding
        );

        ImGui::SetNextWindowPos(
            windowPos,
            ImGuiCond_Always,
            ImVec2(1.0f, 0.0f)
        );

        if (ImGui::Begin(
            "PausedButton",
            nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoMove
        )) {
            ImGui::TextColored(
                ImVec4(1.0f, 0.8f, 0.0f, 1.0f),
                "PAUSED"
            );

            ImGui::Separator();

            if (ImGui::Button(
                "OPEN DASHBOARD",
                ImVec2(140, 45)
            )) {
                showFullMenu = true;
            }
        }

        ImGui::End();
        return;
    }

    // =========================================================
    // STATE 3: FULL DASHBOARD
    // =========================================================
    ImGui::SetNextWindowPos(
        viewport->GetCenter(),
        ImGuiCond_Always,
        ImVec2(0.5f, 0.5f)
    );

    ImGui::SetNextWindowSize(
        ImVec2(800, 570),
        ImGuiCond_Always
    );

    ImGui::Begin(
        "Scenario Manager",
        nullptr,
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove
    );

    ImGui::SetWindowFontScale(1.2f);

    // =========================================================
    // HEADER
    // =========================================================
    ImGui::Text("Simulation Control Center");
    ImGui::Separator();
    ImGui::Spacing();

    // =========================================================
    // ENGINE SELECTION
    // =========================================================
    ImGui::Text("1. Select Propulsion Model:");

    const char* engineNames[] = {
        "Holonomic Model",
        "Ackermann Steering",
        "Unicycle Model"
    };

    ImGui::PushItemWidth(-1);

    ImGui::Combo(
        "##EngineCombo",
        &selectedIdx,
        engineNames,
        IM_ARRAYSIZE(engineNames)
    );

    ImGui::PopItemWidth();

    ImGui::Spacing();

    // =========================================================
    // LIVE CONFIGURATION
    // =========================================================
    ImGui::Text("Live Configuration:");

    ImGui::BeginChild(
        "TopConfigChild",
        ImVec2(0, 180),
        true
    );

    ImGui::TextColored(
        ImVec4(0.4f, 1.0f, 0.4f, 1.0f),
        "System Status: STANDBY"
    );

    ImGui::Separator();

    // Agent count
    ImGui::SliderInt(
        "Num Agents##configSlider",
        &numAgents,
        1,
        50
    );

    // Trajectory selection
    const char* trajectories[] = {
        "Circle",
        "Lemniscate"
    };

    ImGui::Combo(
        "Trajectory##trajCombo",
        &selectedTraj,
        trajectories,
        IM_ARRAYSIZE(trajectories)
    );

    // 3D model selection
    const char* models[] = {
        "Airplane",
        "Car",
        "Drone"
    };

    ImGui::Combo(
        "3D Model##modelCombo",
        &selectedModel,
        models,
        IM_ARRAYSIZE(models)
    );

    // Reset button
    if (ImGui::Button(
        "Reset Scene Positions##resetBtn",
        ImVec2(-1, 35)
    )) {
        triggerReset = true;
    }

    ImGui::EndChild();

    ImGui::Spacing();

    // =========================================================
    // MODEL DESCRIPTION
    // =========================================================
    ImGui::Text("Model Description:");

    ImGui::BeginChild(
        "DescChild",
        ImVec2(0, 120),
        true
    );

    ImGui::TextWrapped(
        "Currently Selected: %s",
        engineNames[selectedIdx]
    );

    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextWrapped(
        "This model handles the mathematical constraints "
        "of agent movement. Ensure the environment scale "
        "matches the propulsion dynamics."
    );

    ImGui::EndChild();

    // =========================================================
    // ACTION BUTTON
    // =========================================================
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    float buttonHeight = 70.0f;

    ImGui::PushStyleColor(
        ImGuiCol_Button,
        ImVec4(0.15f, 0.5f, 0.15f, 1.0f)
    );

    ImGui::PushStyleColor(
        ImGuiCol_ButtonHovered,
        ImVec4(0.2f, 0.7f, 0.2f, 1.0f)
    );

    if (ImGui::Button(
        "INICIAR SIMULACION",
        ImVec2(-1, buttonHeight)
    )) {
        isSimulating = true;
        showFullMenu = false;
    }

    ImGui::PopStyleColor(2);

    ImGui::End();
}

void UI::RenderSimulationPanel(bool isSimulating) {
}