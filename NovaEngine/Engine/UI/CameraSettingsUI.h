#pragma once

#include "Events/CameraEvent.h"
#include "Events/EventQueue.h"
#include "ManagerUI.h"

namespace Nova {
	class CameraSettingsUI : public ManagerUI {
	public:
		CameraSettingsUI();

		void drawUI() override;
	private:
		float movementSpeed;
		float fieldOfView;
		float nearClip;
		long farClip;

		EventQueue& eventQueue = EventQueue::getInstance();
	};
}