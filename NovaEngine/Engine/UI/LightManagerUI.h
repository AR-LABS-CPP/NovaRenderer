#pragma once

#include "Structs/LightStructs.h"
#include "Events/LightEvent.h"
#include "Events/EventQueue.h"

namespace Nova {
	struct LightNode {
		const char* Name;
		const char* Type;
		int Size;
		int ChildIdx;
		int ChildCount;

		inline static ImGuiTableFlags flags = ImGuiTableFlags_BordersV
			| ImGuiTableFlags_BordersOuterH
			| ImGuiTableFlags_Resizable
			| ImGuiTableFlags_RowBg
			| ImGuiTableFlags_NoBordersInBody;
		inline static ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_SpanAllColumns;

		virtual void DisplayNode(const LightNode* node, const LightNode* allNodes) = 0;

	protected:
		void DisplayCommonNode(const LightNode* node, const LightNode* allNodes) {
			ImGui::TableNextRow();
			ImGui::TableNextColumn();

			const bool isFolder = (node->ChildCount > 0);
			if (isFolder) {
				bool open = ImGui::TreeNodeEx(node->Name, treeNodeFlags);
				ImGui::TableNextColumn();
				ImGui::TextDisabled("--");
				ImGui::TableNextColumn();
				ImGui::TextUnformatted(node->Type);

				if (open) {
					for (int nChild = 0; nChild < node->ChildCount; nChild++) {
						DisplayNode(&allNodes[node->ChildIdx + nChild], allNodes);
					}
					ImGui::TreePop();
				}
			}
			else {
				ImGui::TreeNodeEx(node->Name, treeNodeFlags
					| ImGuiTreeNodeFlags_Leaf
					| ImGuiTreeNodeFlags_Bullet
					| ImGuiTreeNodeFlags_NoTreePushOnOpen);
				ImGui::TableNextColumn();
				ImGui::Text("%d", node->Size);
				ImGui::TableNextColumn();
				ImGui::TextUnformatted(node->Type);
			}
		}
	};

	struct SpotLightNode : public LightNode {
		SpotLightNode(const std::vector<std::string>& colNames, float& colSize)
			: colNames(colNames), colSize(colSize) {}

		void DisplayNode(const LightNode* node, const LightNode* allNodes) override {
			DisplayCommonNode(node, allNodes);
		}

		std::vector<std::string> colNames;
		float colSize;
	};

	struct PointLightNode : public LightNode {
		PointLightNode(const std::vector<std::string>& colNames, float& colSize)
			: colNames(colNames), colSize(colSize) {}

		void DisplayNode(const LightNode* node, const LightNode* allNodes) {
			DisplayCommonNode(node, allNodes);
		}

		std::vector<std::string> colNames;
		float colSize;
	};

	class LightManagerUI {
	public:
		LightManagerUI(
			std::unordered_map<GLint, SpotLightStruct>& spotLights,
			std::unordered_map<GLint, PointLightStruct>& pointLights,
			std::vector<std::string>& spotLightTableCols,
			std::vector<std::string>& pointLightTableCols
		);

		void setupTableColumns(const std::vector<std::string>& colNames);
		void drawSpotLightTable();
		void drawPointLightTable();
	private:
		std::unordered_map<GLint, SpotLightStruct> spotLights;
		std::unordered_map<GLint, PointLightStruct> pointLights;

		std::vector<std::string> spotLightTableCols;
		std::vector<std::string> pointLightTableCols;
	};
}