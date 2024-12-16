#include "pch.h"
#include "CameraSettingsUI.h"

namespace Nova {
	CameraSettingsUI::CameraSettingsUI()
		: movementSpeed(2.5), fieldOfView(45.0f),
		  nearClip(0.1f), farClip(100000.0f) {}

	void CameraSettingsUI::drawUI() {
		ImGui::Text("Camera Settings");
		if (ImGui::SliderFloat("Field of View", &fieldOfView, 10.0f, 180.0f)) {
			CameraFieldOfViewChangedEvent camFOVChangedEvent(fieldOfView);
			EventQueue::getInstance().enqueue(std::make_unique<CameraFieldOfViewChangedEvent>(camFOVChangedEvent));
		}

		if(ImGui::InputFloat("Near Clip", &nearClip)) {
			CameraNearClipChangedEvent camNearClipChangeEvent(nearClip);
			EventQueue::getInstance().enqueue(std::make_unique<CameraNearClipChangedEvent>(camNearClipChangeEvent));
		}
		
		if (ImGui::InputScalar("Far Clip", ImGuiDataType_S32, &farClip, NULL, NULL, "%lld")) {
			CameraFarClipChangedEvent camFarClipChangeEvent(farClip);
			EventQueue::getInstance().enqueue(std::make_unique<CameraFarClipChangedEvent>(camFarClipChangeEvent));
		}

		if (ImGui::InputFloat("Speed", &movementSpeed, 1.0f, 10.0f)) {
			CameraMovementSpeedChangedEvent camMoveSpeedChangedEvent(movementSpeed);
			EventQueue::getInstance().enqueue(std::make_unique<CameraMovementSpeedChangedEvent>(camMoveSpeedChangedEvent));
		}

		ImGui::Separator();
	}
}