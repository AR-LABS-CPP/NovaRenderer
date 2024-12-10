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

namespace Nova {
	class Engine {
	public:
		Engine() = default;
		~Engine();

		void initializeAndRun();
		void subscribeToEvents();
		void shutdown();
	private:
		Nova::LogManager logManager;
		Nova::ModelManager modelManager;

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