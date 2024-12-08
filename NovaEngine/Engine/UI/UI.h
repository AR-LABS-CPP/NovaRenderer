#pragma once

#include "Log/Log.h"
#include "Model.h"
#include "Window.h"
#include "Renderer/FrameBuffer.h"

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
	private:
		Window* attachedWindow;
	};
}