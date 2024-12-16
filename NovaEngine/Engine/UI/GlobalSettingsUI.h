#pragma once

#include "Events/GlobalEvent.h"
#include "Events/EventQueue.h"
#include "ManagerUI.h"

namespace Nova {
	class GlobalSettingsUI : public ManagerUI {
	public:
		GlobalSettingsUI();

		void drawUI() override;
	private:
		ImVec4 bgColor;
		bool wireframe;
		int polyMode;

		EventQueue& evtQueue = EventQueue::getInstance();
	};
}