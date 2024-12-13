#include "pch.h"
#include "GlobalSettingsUI.h"

namespace Nova {
	GlobalSettingsUI::GlobalSettingsUI()
		: bgColor(ImVec4(0.1, 0.1, 0.1, 1.0)), wireframe(false), polyMode(GL_FILL) {}

	void GlobalSettingsUI::drawUI() {
		ImGui::Text("Global Settings");
		if (ImGui::ColorEdit4("Background Color", (float*)&bgColor)) {
			BackgroundColorChangedEvent bgColorChangedEvent(bgColor);
			EventQueue::getInstance().enqueue(std::make_unique<BackgroundColorChangedEvent>(bgColorChangedEvent));
		}

		if (ImGui::Checkbox("Wireframe Mode", &wireframe)) {
			glPolygonMode(GL_FRONT_AND_BACK, polyMode == GL_FILL ? GL_LINE : GL_FILL);
			
			if (polyMode == GL_FILL) {
				polyMode = GL_LINE;
			}
			else {
				polyMode = GL_FILL;
			}
		}

		if (ImGui::Button("Reset All", ImVec2(-1, 0))) {
			// TODO: implement the logic
		}

		ImGui::Separator();
	}
}