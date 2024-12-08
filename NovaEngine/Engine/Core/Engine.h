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
#include "Log/Log.h"
#include "Renderer/FrameBuffer.h"
#include "UI/UI.h"
#include "Log/Logging.h"

namespace Nova {
	class Engine {
	public:
		Engine() = default;
		~Engine();

		void initializeAndRun();
		void shutdown();
	private:
		Nova::LogManager logManager;
	};
}