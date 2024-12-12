#pragma once

#include "Structs/LightStructs.h"
#include "LightManager.h"
#include "ManagerUI.h"
#include <glm/glm.hpp>

namespace Nova {
	/*struct LightNode {
		const char* Name;
		const char* Type;

		inline static ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_SpanAllColumns;

		virtual void displayNode() = 0;
	};

	struct SpotLightNode : public LightNode {
		SpotLightStruct& lightStruct;

		SpotLightNode(SpotLightStruct& lightStruct)
			: lightStruct(lightStruct) {
			Name = "Spot Light";
			Type = "SpotLightStruct";
		}

		void displayNode() override {
			if (ImGui::TreeNode(Name)) {
				ImGui::Text("Type: %s", Type);

				if (ImGui::TreeNode("Position")) {
					ImGui::DragFloat3("##Position", glm::value_ptr(lightStruct.position), 0.1f);
					ImGui::TreePop();
				}

				if (ImGui::TreeNode("Direction")) {
					ImGui::DragFloat("##Direction", glm::value_ptr(lightStruct.direction), 0.1f);
				}

				ImGui::TreePop();
			}
		}
	};*/

	class LightManagerUI : public ManagerUI {
	public:
		LightManagerUI() = default;
		explicit LightManagerUI(
			LightManager& lightManager
		);

		void drawUI() override;

	private:
		LightManager& lightManager;
		EventQueue& evtQueue = EventQueue::getInstance();
	};
}