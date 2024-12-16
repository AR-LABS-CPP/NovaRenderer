#include "pch.h"
#include "LightManagerUI.h"

namespace Nova {
	LightManagerUI::LightManagerUI(
		LightManager& lightManager
	) : lightManager(lightManager) {}

    void LightManagerUI::drawUI() {
        ImGui::Text("Lighting Options");
        ImGui::Separator();
        ImGui::Text("Directional Light");

        auto& dirLight = lightManager.getDirectionalLight();

        if (ImGui::Checkbox("Enable Directional Light", &lightManager.isDirectionalLightActive)) {
            if (lightManager.isDirectionalLightActive == 0) {
                evtQueue.enqueue(std::make_unique<DirectionalLightRemovedEvent>());
            }
            else {
                evtQueue.enqueue(std::make_unique<DirectionalLightAddedEvent>());
            }
        }
        
        ImGui::DragFloat3("Direction", glm::value_ptr(dirLight.directionalLight.direction), 0.1f, -FLT_MIN, FLT_MAX);
        ImGui::ColorEdit3("Color", glm::value_ptr(dirLight.directionalLight.color));

        if (ImGui::Button("Add Spot Light", ImVec2(-1, 0))) {
            evtQueue.enqueue(std::make_unique<SpotLightAddedEvent>());
        }
        if (ImGui::Button("Add Point Light", ImVec2(-1, 0))) {
            evtQueue.enqueue(std::make_unique<PointLightAddedEvent>());
        }

        ImGui::Separator();
        ImGui::Text("Spot Lights");
        auto& spotLights = lightManager.getSpotLigts();
        
        for (auto& [id, sl] : spotLights) {
            ImGui::PushID(id);
            if (ImGui::CollapsingHeader(("Spot Light " + std::to_string(id)).c_str())) {
                ImGui::DragFloat3("Position", glm::value_ptr(sl.position), 0.1f, -FLT_MIN, FLT_MAX);
                ImGui::DragFloat3("Direction", glm::value_ptr(sl.direction), 0.1f, -FLT_MIN, FLT_MAX);
                ImGui::DragFloat3("Ambient", glm::value_ptr(sl.ambient), 0.1f);
                ImGui::DragFloat3("Diffuse", glm::value_ptr(sl.diffuse), 0.1f);
                ImGui::DragFloat3("Specular", glm::value_ptr(sl.specular), 0.1f);
                ImGui::ColorEdit3("Color", glm::value_ptr(sl.color));
                ImGui::DragFloat("Constant", &sl.constant, 0.1f);
                ImGui::DragFloat("Linear", &sl.linear, 0.1f);
                ImGui::DragFloat("Quadratic", &sl.quadratic, 0.1f);
                ImGui::DragFloat("CutOff", &sl.cutOff, 0.1f);
                ImGui::DragFloat("OuterCutOff", &sl.outerCutOff, 0.1f);

            }
            ImGui::PopID();
        }

        ImGui::Separator();
        ImGui::Text("Point Lights");
        auto& pointLights = lightManager.getPointLights();

        for (auto& [id, pl] : pointLights) {
            ImGui::PushID(id);
            if (ImGui::CollapsingHeader(("Point Light " + std::to_string(id)).c_str())) {
                ImGui::DragFloat3("Position", glm::value_ptr(pl.position), 0.1f, -FLT_MIN, FLT_MAX);
                ImGui::DragFloat3("Ambient", glm::value_ptr(pl.ambient), 0.1f);
                ImGui::DragFloat3("Diffuse", glm::value_ptr(pl.diffuse), 0.1f);
                ImGui::DragFloat3("Specular", glm::value_ptr(pl.specular), 0.1f);
                ImGui::ColorEdit3("Color", glm::value_ptr(pl.color), 0.1f);
                ImGui::DragFloat("Constant", &pl.constant, 0.1f);
                ImGui::DragFloat("Linear", &pl.linear, 0.1f);
                ImGui::DragFloat("Quadratic", &pl.quadratic, 0.1f);
            }
            ImGui::PopID();
        }
    }
}