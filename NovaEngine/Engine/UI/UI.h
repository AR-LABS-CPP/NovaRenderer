#pragma once

#include "pch.h"
#include "Model.h"
#include "Window.h"
#include "Log/Log.h"
#include "Renderer/FrameBuffer.h"
#include "Events/EventBus.h"
#include "Events/EventQueue.h"
#include "Events/LightEvent.h"
#include "Events/ModelEvent.h"
#include <windows.h>
#include <commdlg.h>
#include <stdlib.h>

namespace Nova {
	class UI {
	public:
		static bool directionalLightActive;

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

		ImGuiWindowFlags addDockSpaceFlags();
		ImGuiID addDockSpace();
		void initializeDockSpace(ImGuiWindowFlags dockspaceFlags, ImGuiID dockspaceId);

		void drawFPSAndMs();
		void addModelOptions();
		void addLightingOptions();
		void addColorOption();
		void addGizmoOptions();
		void addMaterialOptions();
		void addCameraOptions();
		void addGlobalOptions();
	private:
		Window* attachedWindow;
		
		EventQueue& evtQueue = EventQueue::getInstance();
	};
}