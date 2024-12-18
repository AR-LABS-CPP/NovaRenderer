#include "pch.h"
#include "UI.h"

namespace Nova {
	bool UI::directionalLightActive = false;

	UI::UI(
		Window* currentWindow,
		LightManagerUI* lightManagerUI,
		GlobalSettingsUI* globalSettingsUI,
		CameraSettingsUI* cameraSettingsUI
	) : lightManagerUI(lightManagerUI),
		globalSettingsUI(globalSettingsUI),
		cameraSettingsUI(cameraSettingsUI),
		attachedWindow(currentWindow),
		sceneBuffer(sceneBuffer)
	{}

	void UI::initializeUI() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable
			| ImGuiConfigFlags_NavEnableKeyboard
			| ImGuiConfigFlags_NavEnableGamepad;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(attachedWindow->getWindowObject(), true);
		ImGui_ImplOpenGL3_Init("#version 460 core");

		NOVA_INFO("UI initialized");
	}

	void UI::updateUI() {}

	void UI::createNewUIFrame() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void UI::renderUIFrame(FrameBuffer& sceneBuffer) {
		ImGuiWindowFlags windowFlags = addDockSpaceFlags();
		ImGuiID dockspace = addDockSpace();
		initializeDockSpace(windowFlags, dockspace);

		createSceneView(sceneBuffer.getTexture());
		createOptionsPanel();
		createLogsPanel();
		createCommandsPanel();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void UI::createSceneView(GLuint textureId) {
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
		ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
		sceneViewWidth = ImGui::GetContentRegionAvail().x;
		sceneViewHeight = ImGui::GetContentRegionAvail().y;
		ImGui::Image(
			(ImTextureID)textureId,
			ImVec2(sceneViewWidth, sceneViewHeight),
			ImVec2(0, 1),
			ImVec2(1, 0)
		);
		ImGui::End();
		ImGui::PopStyleColor();
	}

	void UI::createOptionsPanel() {
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
		ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiCond_Always);

		if (ImGui::Begin("Options", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse)) {
			globalSettingsUI->drawUI();
			drawFPSAndMs();
			addModelOptions();
			addGizmoOptions();
			cameraSettingsUI->drawUI();
			addMaterialOptions();
			lightManagerUI->drawUI();
		}
		ImGui::End();
		ImGui::PopStyleColor();
	}

	void UI::createLogsPanel() {
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
		ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiCond_Always);
		ImGui::Begin("Logs", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
		ImGui::Text("Logs Content");
		ImGui::End();
		ImGui::PopStyleColor();
	}

	void UI::createCommandsPanel() {
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
		ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiCond_Always);
		ImGui::Begin("Commands", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
		ImGui::Text("Commands Content");
		ImGui::End();
		ImGui::PopStyleColor();
	}

	void UI::shutdownUI() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		NOVA_WARN("UI destroyed");
	}

	bool UI::wantsToCaptureMouse() {
		return ImGui::GetIO().WantCaptureMouse;
	}

	bool UI::wantsToCaptureKeyboard() {
		return ImGui::GetIO().WantCaptureKeyboard;
	}

	// yeah I know, Win32 with ImGui in an OpenGL project, lol
	std::string UI::showFileDialog() {
		OPENFILENAME openFileName;
		wchar_t szFile[260];

		RtlSecureZeroMemory(&openFileName, sizeof(openFileName));
		openFileName.lStructSize = sizeof(openFileName);
		openFileName.hwndOwner = NULL;
		openFileName.nFilterIndex = 1;
		openFileName.lpstrFile = szFile;
		openFileName.nMaxFile = sizeof(szFile);
		openFileName.lpstrFilter = L".obj";
		openFileName.nFilterIndex = 1;
		openFileName.lpstrFile[0] = '\0';
		openFileName.lpstrFileTitle = NULL;
		openFileName.nMaxFileTitle = 0;
		openFileName.lpstrInitialDir = L".";
		openFileName.lpstrTitle = L"Select a model";
		openFileName.Flags = OFN_PATHMUSTEXIST
			| OFN_FILEMUSTEXIST
			| OFN_READONLY;

		if (GetOpenFileName(&openFileName) == TRUE) {
			// depends on where you are (can make it flexible but doesn't matter for now)
			auto locale = std::setlocale(LC_ALL, "en_US.utf8");
			NOVA_ASSERT(locale != nullptr, "Locale must be set before converting wide char to string");
			std::string convertedFileName = convertWideString(openFileName.lpstrFile);

			return convertedFileName;
		}

		NOVA_WARN("Selected file name is not supposed to be null");
		return "";
	}

	std::string UI::convertWideString(const std::wstring& wstr) {
		// Maximum size for a single multi-byte character, typically 4-6 bytes
		const int BUFF_SIZE = 7;

		NOVA_ASSERT(MB_CUR_MAX < BUFF_SIZE, "Buffer size must be greater");

		std::string result;

		for (const wchar_t wc : wstr) {
			std::array<char, BUFF_SIZE> buffer = {};
			int bytesWritten = 0;
			errno_t err = wctomb_s(&bytesWritten, buffer.data(), buffer.size(), wc);

			NOVA_ASSERT(err == 0 || bytesWritten != 0, "Characters must be in multi-byte");
			result.append(buffer.data(), bytesWritten);
		}

		return result;
	}

	ImGuiWindowFlags UI::addDockSpaceFlags() {
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGuiWindowFlags windowFlags =ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoCollapse 
			| ImGuiWindowFlags_NoMove 
			| ImGuiWindowFlags_NoNavFocus 
			| ImGuiWindowFlags_NoBringToFrontOnFocus;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace", nullptr, windowFlags);
		ImGui::PopStyleVar(3);

		return windowFlags;
	}

	ImGuiID UI::addDockSpace() {
		ImGuiID dockspaceId = ImGui::GetID("NovaDockspace");
		ImGuiDockNodeFlags flags = ImGuiDockNodeFlags_NoSplit;

		ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), flags);
		ImGui::End();

		return dockspaceId;
	}

	void UI::initializeDockSpace(ImGuiWindowFlags dockspaceFlags, ImGuiID dockspaceId) {
		static bool first_time = true;
		if (first_time) { 
			first_time = false;

			ImGui::DockBuilderRemoveNode(dockspaceId);
			ImGui::DockBuilderAddNode(dockspaceId, dockspaceFlags);

			auto dock_main = dockspaceId;
			auto dock_options = ImGui::DockBuilderSplitNode(dock_main, ImGuiDir_Left, 0.2f, nullptr, &dock_main);
			auto dock_commands = ImGui::DockBuilderSplitNode(dock_main, ImGuiDir_Right, 0.2f, nullptr, &dock_main);
			auto dock_logs = ImGui::DockBuilderSplitNode(dock_main, ImGuiDir_Down, 0.3f, nullptr, &dock_main);
			auto dock_scene = dock_main;

			ImGui::DockBuilderDockWindow("Options", dock_options);
			ImGui::DockBuilderDockWindow("Scene", dock_scene);
			ImGui::DockBuilderDockWindow("Commands", dock_commands);
			ImGui::DockBuilderDockWindow("Logs", dock_logs);

			ImGui::DockBuilderFinish(dockspaceId);
		}
	}

	void UI::drawFPSAndMs() {
		ImGuiIO& io = ImGui::GetIO();
		float frameTimeMs = 1000.0f / io.Framerate;

		ImGui::Text("Application Stats:");
		ImGui::Text("FPS: %.1f", io.Framerate);
		ImGui::Text("Frame Time: %.3f ms/frame", frameTimeMs);
		ImGui::Separator();
	}

	void UI::addModelOptions() {
		ImGui::Text("Model Options");
		static bool loadModelPressed = false;
		if (ImGui::Button("Load Model", ImVec2(-1, 0))) {
			loadModelPressed = true;
		}

		if (loadModelPressed) {
			std::string filePath = showFileDialog();

			if (!filePath.empty()) {
				ModelSelectedEvent modelSelectedEvent(filePath);
				evtQueue.enqueue(std::make_unique<ModelSelectedEvent>(modelSelectedEvent));
			}
			else {
				NOVA_WARN("Model file path cannot be zero or empty");
			}

			loadModelPressed = false;
		}
		ImGui::Separator();
	}

	void UI::addColorOption() {}

	void UI::addGizmoOptions() {
		ImGui::Text("Transform Object (X, Y, Z)");
		static float translation[3] = { 0.0f, 0.0f, 0.0f };
		ImGui::InputFloat3("Translate", translation);

		static float rotation[3] = { 0.0f, 0.0f, 0.0f };
		ImGui::InputFloat3("Rotate", rotation);

		static float scale[3] = { 1.0f, 1.0f, 1.0f };
		ImGui::InputFloat3("Scale ", scale);
		ImGui::Separator();
	}

	void UI::addMaterialOptions() {
		ImGui::Text("Material Settings");
		static ImVec4 albedoColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ImGui::ColorEdit4("Albedo Color", (float*)&albedoColor);

		static float metallic = 0.0f;
		ImGui::SliderFloat("Metallic", &metallic, 0.0f, 1.0f);

		static float roughness = 1.0f;
		ImGui::SliderFloat("Roughness", &roughness, 0.0f, 1.0f);
		ImGui::Separator();
	}

	void UI::overlayModelInfoInSceneView(const Model& model) {}

	int UI::getSceneViewWidth() {
		return sceneViewWidth;
	}

	int UI::getSceneViewHeight() {
		return sceneViewHeight;
	}
}