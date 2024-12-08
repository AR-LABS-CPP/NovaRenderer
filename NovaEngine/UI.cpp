#include "pch.h"
#include "UI.h"
#include "Log.h"
#include "Model.h"

namespace Nova {
	UI::UI(Window& currentWindow) {
		attachedWindow = currentWindow;
	}

	void UI::initializeUI() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable
			| ImGuiConfigFlags_NavEnableKeyboard
			| ImGuiConfigFlags_NavEnableGamepad;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(attachedWindow.getWindowObject(), true);
		ImGui_ImplOpenGL3_Init("#version 460 core");

		NOVA_INFO("UI initialized");
	}

	void UI::createNewUIFrame() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void UI::renderUIFrame(FrameBuffer& sceneBuffer) {
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGuiWindowFlags window_flags =
			ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoNavFocus |
			ImGuiWindowFlags_NoBringToFrontOnFocus;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace", nullptr, window_flags);
		ImGui::PopStyleVar(3);

		ImGuiID dockspace_id = ImGui::GetID("NovaDockspace");
		ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_NoSplit;

		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		ImGui::End();

		static bool first_time = true;
		if (first_time) {
			first_time = false;

			ImGui::DockBuilderRemoveNode(dockspace_id);
			ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags);

			auto dock_main = dockspace_id;
			auto dock_options = ImGui::DockBuilderSplitNode(dock_main, ImGuiDir_Left, 0.2f, nullptr, &dock_main);
			auto dock_commands = ImGui::DockBuilderSplitNode(dock_main, ImGuiDir_Right, 0.2f, nullptr, &dock_main);
			auto dock_logs = ImGui::DockBuilderSplitNode(dock_main, ImGuiDir_Down, 0.3f, nullptr, &dock_main);
			auto dock_scene = dock_main;

			ImGui::DockBuilderDockWindow("Options", dock_options);
			ImGui::DockBuilderDockWindow("Scene", dock_scene);
			ImGui::DockBuilderDockWindow("Commands", dock_commands);
			ImGui::DockBuilderDockWindow("Logs", dock_logs);

			ImGui::DockBuilderFinish(dockspace_id);
		}

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
		float width = ImGui::GetContentRegionAvail().x;
		float height = ImGui::GetContentRegionAvail().y;
		ImGui::Image(
			(ImTextureID)textureId,
			ImVec2(width, height),
			ImVec2(0, 1),
			ImVec2(1, 0)
		);
		ImGui::End();
		ImGui::PopStyleColor();
	}

	void UI::createOptionsPanel() {
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
		ImGui::Begin("Options", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
		ImGui::Text("Options Content");
		ImGui::End();
		ImGui::PopStyleColor();
	}

	void UI::createLogsPanel() {
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
		ImGui::Begin("Logs", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
		ImGui::Text("Logs Content");
		ImGui::End();
		ImGui::PopStyleColor();
	}
	
	void UI::createCommandsPanel() {
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
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
}