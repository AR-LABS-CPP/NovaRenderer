#include "pch.h"
#include "Engine.h"

namespace Nova {
	void Engine::initializeAndRun() {
		subscribeToEvents();

		logManager = Nova::LogManager();
		logManager.initialize();

		NOVA_INFO("Logger initialized");

		Nova::Window mainWindow;
		if (!mainWindow.setupWindow()) {
			NOVA_ERROR("Failed to create GLFW window!");
		}

		Nova::Shader objectShader = Nova::ShaderBuilder()
			.withVertexShader("Shaders/Object/ObjectVertexShader.vert")
			.withFragmentShader("Shaders/Object/ObjectFragmentShader.frag")
			.buildShader();
		
		int windowWidth = mainWindow.getWindowWidth();
		int windowHeight = mainWindow.getWindowHeight();

		Nova::Camera camera(
			-90.0f,
			0.0f,
			windowWidth / 2,
			windowHeight / 2,
			0.6f,
			2.5f,
			45.0f,
			windowWidth / windowHeight,
			windowWidth,
			windowHeight
		);

		// mainWindow.setCamera(&camera);

		std::string modelPath = "Models/backpack/backpack.obj";
		std::string cubePath = "Models/cube/cube.obj";

		Nova::Model backpackModel(modelPath, 1);
		Nova::Model cubeModel(cubePath, 2);

		glm::vec3 lightDir(0.0f, 0.0f, -4.0f);

		Nova::DirectionalLight directionalLight(
			lightDir
		);

		std::vector<Nova::SpotLight> spotLights;

		Nova::SpotLight spotLight(
			camera.getCameraPosition(),
			camera.getCameraFront()
		);

		spotLights.push_back(spotLight);

		Nova::LightManager lightManager;

		NOVA_INFO("Engine initialized");

		FrameBuffer sceneBuffer(
			windowWidth,
			windowHeight
		);
		
		Nova::UI novaUi(&mainWindow);
		novaUi.initializeUI();

		std::unordered_map<GLuint, Model> models;
		models[backpackModel.modelId] = backpackModel;

		while(!mainWindow.windowShouldClose()) {
			novaUi.createNewUIFrame();
			sceneBuffer.bindBuffer(mainWindow.getWindowWidth(), mainWindow.getWindowHeight());
			
			mainWindow.update(glm::vec4(0.1, 0.1, 0.1, 1.0));

			objectShader.setInt("nPointLights", 0);
			objectShader.setInt("nSpotLights", 0);
			objectShader.setInt("directionalLightActive", 1);

			objectShader.useShader();
			objectShader.setVec3("viewerPos", camera.getCameraPosition());
			objectShader.setMat4("projection", camera.getProjectionMatrix());
			objectShader.setMat4("view", camera.getViewMatrix());
			objectShader.setMat4("model", glm::mat4(1.0));

			lightManager.applyDirectionalLight(objectShader, directionalLight, lightDir);
			
			for (auto& it : models) {
				it.second.drawModel(objectShader, mainWindow.getWindowWidth(), mainWindow.getWindowHeight());
			}

			sceneBuffer.unbindBuffer();
			novaUi.renderUIFrame(sceneBuffer);
			mainWindow.swap();
		}

		novaUi.shutdownUI();
	}

	void Engine::subscribeToEvents() {
		EventBus::getInstance().subscribe<WindowResizeEvent>([this](Event& event) {
			onWindowResize(event);
		});

		NOVA_INFO("Engine subsribed to events");
	}

	void Engine::shutdown() {
		NOVA_WARN("Engine shutting down");
		
		logManager.shutdown();
	}

	Engine::~Engine() {
		shutdown();
	}
}