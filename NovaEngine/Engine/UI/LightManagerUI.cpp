#include "pch.h"
#include "LightManagerUI.h"

namespace Nova {
	LightManagerUI::LightManagerUI(
		LightManager& lightManager
	) : lightManager(lightManager) {}

	void LightManagerUI::drawLightsUI() {
		if (ImGui::Begin("Lights Manager")) {
			auto& spotLights = lightManager.getSpotLigts();
			auto& pointLights = lightManager.getPointLights();

			for (auto& [id, sl] : spotLights) {
				ImGui::PushID(id);
				if (ImGui::CollapsingHeader(("Spot Light " + std::to_string(id)).c_str())) {
					ImGui::DragFloat3("Position", glm::value_ptr(sl.spotLight.position), 0.1f);
					ImGui::DragFloat3("Direction", glm::value_ptr(sl.spotLight.direction), 0.1f);
					ImGui::ColorEdit3("Color", glm::value_ptr(sl.spotLight.color));
				}
				ImGui::PopID();
			}
		}

		ImGui::End();
	}
}