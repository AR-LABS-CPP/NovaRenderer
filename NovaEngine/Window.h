#pragma once

#include "Camera.h"

namespace Nova {
	class Window {
	public:
		Window();
		Window(
			GLuint widowWidth, GLuint windowHeight,
			GLuint majorVersion, GLuint minorVersion
		);
		~Window();

		bool setupWindow();
		bool windowShouldClose();
		void setCamera(Camera* camera);
		void update(glm::vec4 clearColor);
		void swap();

		GLfloat getXChange();
		GLfloat getYChange();

		// use with care
		GLFWwindow* getWindowObject();

		int getWindowWidth();
		int getWindowHeight();

		void setWindowWidth(int newWidth);
		void setWindowHeight(int newHeight);

		Camera& getAttachedCamera();
	private:
		GLFWwindow* mainWindow;
		GLuint windowWidth, windowHeight;
		GLuint majorVersion, minorVersion;
		int bufferWidth, bufferHeight;

		bool keys[1024];
		bool isOrbiting = false;
		bool isPanning = false;
		bool isZooming = false;

		GLfloat lastX, lastY;
		GLfloat xChange, yChange;
		bool mouseFirstMoved;

		GLdouble lastFrameTime = 0.0;
		GLdouble deltaTime = 0.0;

		Camera* camera;
		bool hasCamera = false;

		static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
		static void handleMouse(GLFWwindow* window, double xPos, double yPos);
		static void handleMouseButton(GLFWwindow* window, int button, int action, int mods);
		static void handleScroll(GLFWwindow* window, double xOffset, double yOffset);
		static void frameResizeCallback(GLFWwindow* window, int width, int height);
		void createCallbacks();
	};
}