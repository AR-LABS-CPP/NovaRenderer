#include "pch.h"
#include "LightManagerUI.h"

namespace Nova {
	LightManagerUI::LightManagerUI(
		std::unordered_map<GLint, SpotLightStruct>& spotLights,
		std::unordered_map<GLint, PointLightStruct>& pointLights,
		std::vector<std::string>& spotLightTableCols,
		std::vector<std::string>& pointLightTableCols
	) : spotLights(spotLights), pointLights(pointLights),
		spotLightTableCols(spotLightTableCols), pointLightTableCols(pointLightTableCols) {}

	void LightManagerUI::setupTableColumns(const std::vector<std::string>& colNames) {
		for (const auto& colName : colNames) {
			ImGui::TableSetupColumn(colName.c_str(), ImGuiTableColumnFlags_WidthFixed);
		}

		ImGui::TableHeadersRow();
	}

	void LightManagerUI::drawSpotLightTable() {
		if (ImGui::BeginTable("SpotLights", spotLightTableCols.size(), LightNode::flags)) {
			setupTableColumns(spotLightTableCols);

			ImGui::EndTable();
		}
	}
	
	void LightManagerUI::drawPointLightTable() {
		if (ImGui::BeginTable("Point Lights", pointLightTableCols.size(), LightNode::flags)) {
			setupTableColumns(pointLightTableCols);

			ImGui::EndTable();
		}
	}
}