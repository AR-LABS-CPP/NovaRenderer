#pragma once

#include "Window.h"
#include "Camera.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Renderer/Shader.h"
#include "Renderer/ShaderBuilder.h"
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

namespace Nova {
	class Engine {
	public:
		Engine() = default;
		~Engine();

		void initializeAndRun();
		void subscribeToEvents();
		void shutdown();

		void initializeLogger();
		void initializeWindow(Window& window);
		void initializeDefaultShaders();
		
		Camera initializeCamera(Window& window);
		
		void initializeDefaultLights();
		void renderAllModels(std::vector<Model> allModels, Shader& objectShader, Window& mainWindow);
	private:
		LogManager logManager;
		ModelManager modelManager;

		void onWindowResize(Event& event) {
			auto& resizeEvent = static_cast<WindowResizeEvent&>(event);
		}

		void onModelLoad(Event& event) {
			auto& modelLoadEvent = static_cast<ModelSelectedEvent&>(event);

			Model model(modelLoadEvent.getModelPath(), 0);
			modelManager.addModel(model);
		}
	};
}