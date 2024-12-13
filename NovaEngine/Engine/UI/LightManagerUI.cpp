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
        ImGui::DragFloat3("Direction", glm::value_ptr(dirLight.direction), 0.1f, -FLT_MIN, FLT_MAX);
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
                ImGui::DragFloat3("Position", glm::value_ptr(sl.spotLight.position), 0.1f, -FLT_MIN, FLT_MAX);
                ImGui::DragFloat3("Direction", glm::value_ptr(sl.spotLight.direction), 0.1f, -FLT_MIN, FLT_MAX);
                ImGui::DragFloat3("Ambient", glm::value_ptr(sl.spotLight.ambient), 0.1f);
                ImGui::DragFloat3("Diffuse", glm::value_ptr(sl.spotLight.diffuse), 0.1f);
                ImGui::DragFloat3("Specular", glm::value_ptr(sl.spotLight.specular), 0.1f);
                ImGui::ColorEdit3("Color", glm::value_ptr(sl.spotLight.color));
                ImGui::DragFloat("Constant", &sl.spotLight.constant, 0.1f);
                ImGui::DragFloat("Linear", &sl.spotLight.linear, 0.1f);
                ImGui::DragFloat("Quadratic", &sl.spotLight.quadratic, 0.1f);
                ImGui::DragFloat("CutOff", &sl.spotLight.cutOff, 0.1f);
                ImGui::DragFloat("OuterCutOff", &sl.spotLight.outerCutOff, 0.1f);

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
                ImGui::DragFloat3("Ambient", glm::value_ptr(pl.pointLight.ambient), 0.1f);
                ImGui::DragFloat3("Diffuse", glm::value_ptr(pl.pointLight.diffuse), 0.1f);
                ImGui::DragFloat3("Specular", glm::value_ptr(pl.pointLight.specular), 0.1f);
                ImGui::ColorEdit3("Color", glm::value_ptr(pl.pointLight.color), 0.1f);
                ImGui::DragFloat("Constant", &pl.pointLight.constant, 0.1f);
                ImGui::DragFloat("Linear", &pl.pointLight.linear, 0.1f);
                ImGui::DragFloat("Quadratic", &pl.pointLight.quadratic, 0.1f);
            }
            ImGui::PopID();
        }
    }
}