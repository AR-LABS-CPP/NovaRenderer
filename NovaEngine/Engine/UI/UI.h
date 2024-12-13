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
#include "Renderer/ShaderManager.h"
#include "ModelManager.h"
#include "LightManagerUI.h"
#include "GlobalSettingsUI.h"
#include <windows.h>
#include <commdlg.h>
#include <stdlib.h>

namespace Nova {
	class UI {
	public:
		static bool directionalLightActive;

		UI() = delete;
		UI(
			Window* currentWindow,
			LightManagerUI* lightManagerUI,
			GlobalSettingsUI* globalSettingsUI
		);
		~UI() = default;

		void initializeUI();
		void updateUI();
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
		void addColorOption();
		void addGizmoOptions();
		void addMaterialOptions();
		void addCameraOptions();

		void overlayModelInfoInSceneView(const Model& model);
	private:
		Window* attachedWindow;
		LightManagerUI* lightManagerUI;
		GlobalSettingsUI* globalSettingsUI;

		EventQueue& evtQueue = EventQueue::getInstance();
	};
}