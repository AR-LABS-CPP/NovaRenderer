#pragma once

#include "pch.h"
#include "Model.h"
#include "Window.h"
#include "Log/Log.h"
#include "Renderer/FrameBuffer.h"
#include "Events/EventBus.h"
#include "Events/ModelEvent.h"
#include <windows.h>
#include <commdlg.h>
#include <stdlib.h>

namespace Nova {
	class UI {
	public:
		UI() = delete;
		UI(Window* currWindow);
		~UI() = default;

		void initializeUI();
		void createNewUIFrame();
		void renderUIFrame(FrameBuffer& sceneBuffer);
		void shutdownUI();

		void createSceneView(GLuint textureId);
		void createOptionsPanel();
		void createLogsPanel();
		void createCommandsPanel();
		
		bool wantsToCaptureMouse();
		bool wantsToCaptureKeyboard();

		std::string showFileDialog();
		std::string convertWideString(const std::wstring& wstr);
	private:
		Window* attachedWindow;
	};
}