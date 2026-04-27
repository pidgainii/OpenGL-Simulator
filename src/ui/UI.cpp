#include "simulator/ui/UI.h"
#include "imgui.h"

UI::UI(Simulation* sim)
    : simulation(sim) {
}

void UI::Render(int& selectedIdx, bool& isSimulating, const std::vector<std::unique_ptr<Engine>>& engines) {
    // 1. Renderizar el selector central (solo si no se está simulando o como gestor)
    RenderScenarioSelector(selectedIdx, isSimulating);

    // 2. Renderizar el panel de control lateral (ajustes de agentes, velocidad, etc.)
    RenderSimulationPanel(isSimulating);
}

void UI::RenderScenarioSelector(int& selectedIdx, bool& isSimulating) {
    // Configuramos la ventana para que aparezca en el centro del viewport
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(350, 180), ImGuiCond_FirstUseEver);

    ImGui::Begin("Scenario Manager", nullptr, ImGuiWindowFlags_NoCollapse);

    ImGui::Text("Select Propulsion Model:");
    ImGui::Spacing();

    // Nombres de los motores disponibles
    const char* engineNames[] = { "Holonomic Model", "Ackermann Steering", "Unicycle Model" };

    // El Combo modifica directamente selectedIdx en Application
    if (ImGui::Combo("##EngineCombo", &selectedIdx, engineNames, IM_ARRAYSIZE(engineNames))) {
        // Si el usuario cambia de motor, podríamos querer pausar la simulación actual
        // isSimulating = false; 
    }

    ImGui::Separator();
    ImGui::Spacing();

    // Botón de acción principal
    if (!isSimulating) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        if (ImGui::Button("RUN SIMULATION", ImVec2(-1, 40))) {
            isSimulating = true;
        }
        ImGui::PopStyleColor();
    }
    else {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.2f, 0.2f, 1.0f));
        if (ImGui::Button("STOP / PAUSE", ImVec2(-1, 40))) {
            isSimulating = false;
        }
        ImGui::PopStyleColor();
    }

    ImGui::End();
}

void UI::RenderSimulationPanel(bool isSimulating) {
    // Panel lateral para parámetros en tiempo real
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::Begin("Simulation Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::CollapsingHeader("Live Configuration", ImGuiTreeNodeFlags_DefaultOpen)) {

        ImGui::Text("Status: %s", isSimulating ? "RUNNING" : "PAUSED");
        ImGui::Separator();


        if (ImGui::Button("Reset Scene", ImVec2(-1, 0))) {
            // Lógica para resetear posiciones si fuera necesario
        }
    }

    ImGui::End();
}