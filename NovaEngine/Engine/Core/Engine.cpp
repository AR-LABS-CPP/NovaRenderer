#include "pch.h"
#include "Engine.h"

namespace Nova {
	void Engine::initializeAndRun() {
		initializeLogger();
		subscribeToEvents();

		Window mainWindow;
		initializeWindow(mainWindow);
		
		Camera camera = initializeCamera(mainWindow);

		Shader objectShader = ShaderBuilder()
			.withVertexShader("Shaders/Object/ObjectVertexShader.vert")
			.withFragmentShader("Shaders/Object/ObjectFragmentShader.frag")
			.buildShader();

		Shader gizmoShader = ShaderBuilder()
			.withVertexShader("Shaders/Gizmo/GizmoVertexShader.vert")
			.withFragmentShader("Shaders/Gizmo/GizmoFragmentShader.frag")
			.buildShader();
		
		FrameBuffer sceneBuffer(
			mainWindow.getWindowWidth(),
			mainWindow.getWindowHeight()
		);
		
		UI novaUi(&mainWindow);
		novaUi.initializeUI();

		while(!mainWindow.windowShouldClose()) {
			novaUi.createNewUIFrame();
			sceneBuffer.bindBuffer(mainWindow.getWindowWidth(), mainWindow.getWindowHeight());
			mainWindow.update(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

			objectShader.setInt("nPointLights", 0);
			objectShader.setInt("nSpotLights", 0);
			objectShader.setInt("directionalLightActive", 1);

			objectShader.useShader();
			objectShader.setVec3("viewerPos", camera.getCameraPosition());
			objectShader.setMat4("projection", camera.getProjectionMatrix());
			objectShader.setMat4("view", camera.getViewMatrix());
			objectShader.setMat4("model", glm::mat4(1.0));

			renderAllModels(modelManager.getAllModels(), objectShader, mainWindow);

			EventQueue::getInstance().process();

			sceneBuffer.unbindBuffer();
			novaUi.renderUIFrame(sceneBuffer);
			mainWindow.swap();
		}

		novaUi.shutdownUI();
	}

	void Engine::initializeLogger() {
		logManager = LogManager();
		logManager.initialize();

		NOVA_INFO("Logger initialized");
	}

	void Engine::initializeWindow(Window& window) {
		if (!window.setupWindow()) {
			NOVA_ERROR("Failed to create GLFW window!");
		}

		NOVA_INFO("Main window initialized");
	}

	void Engine::initializeDefaultShaders() {}

	Camera Engine::initializeCamera(Window& window) {
		int width = window.getWindowWidth();
		int height = window.getWindowHeight();

		Camera camera(
			-90.0f,
			0.0f,
			width / 2,
			height / 2,
			0.6f,
			2.5f,
			45.0f,
			width / height,
			width,
			height
		);

		NOVA_INFO("Main camera initialized");

		return camera;
	}

	void Engine::initializeDefaultLights() {}

	void Engine::renderAllModels(std::vector<Model> allModels, Shader& objectShader, Window& mainWindow) {
		if (allModels.size() > 0) {
			for (auto& it : allModels) {
				it.drawModel(objectShader, mainWindow.getWindowWidth(), mainWindow.getWindowHeight());
			}
		}
	}

	void Engine::subscribeToEvents() {
		EventBus::getInstance().subscribe<WindowResizeEvent>([this](Event& event) {
			onWindowResize(event);
		});

		EventBus::getInstance().subscribe<ModelSelectedEvent>([this](Event& event) {
			onModelLoad(event);
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