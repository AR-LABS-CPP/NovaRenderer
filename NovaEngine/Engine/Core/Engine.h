#pragma once

#include "Window.h"
#include "Camera.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Renderer/Shader.h"
#include "Renderer/ShaderBuilder.h"
#include "Renderer/ShaderManager.h"
#include "Model.h"
#include "LightManager.h"
#include "ModelManager.h"
#include "Log/Log.h"
#include "Renderer/FrameBuffer.h"
#include "UI/UI.h"
#include "Log/Logging.h"
#include "Events/WindowEvent.h"
#include "Events/ModelEvent.h"
#include "Events/EventBus.h"
#include "Events/EventQueue.h"
#include "Gizmo.h"
#include "Vendor/ImGui/ImGuizmo.h"
#include "Skybox.h"

namespace Nova {
	class Engine {
	public:
		Engine();
		~Engine();

		void initializeAndRun();
		void subscribeToEvents();
		void shutdown();

		void initializeLogger();
		void initializeWindow(Window& window);
		void initializeDefaultShaders();
		
		Camera initializeCamera(Window& window);
		
		void renderAllModels(std::vector<Model> allModels, Shader& objectShader, Window& mainWindow);
	private:
		glm::vec4 clearColor;

		LogManager logManager;
		ModelManager modelManager;

		EventQueue& eventQueue = EventQueue::getInstance();

		void onWindowResize(Event& event) {
			auto& resizeEvent = static_cast<WindowResizeEvent&>(event);
		}

		void onModelLoad(Event& event) {
			auto& modelLoadEvent = static_cast<ModelSelectedEvent&>(event);

			Model model(modelLoadEvent.getModelPath(), 0);
			modelManager.addModel(model);
		}

		void onBackgroundColorChanged(Event& event) {
			auto& bgColorChangedEvent = static_cast<BackgroundColorChangedEvent&>(event);

			clearColor.x = bgColorChangedEvent.getXComp();
			clearColor.y = bgColorChangedEvent.getYComp();
			clearColor.z = bgColorChangedEvent.getZComp();
			clearColor.w = bgColorChangedEvent.getWComp();
		}
	};
}