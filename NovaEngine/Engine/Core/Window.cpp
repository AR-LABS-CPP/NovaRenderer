#include "pch.h"
#include "Window.h"

namespace Nova {
	Window::Window()
		: mainWindow(nullptr), windowWidth(0), windowHeight(0),
		majorVersion(4), minorVersion(6), bufferWidth(0), bufferHeight(0) {
	}

	Window::Window(
		GLuint windowWidth, GLuint windowHeight,
		GLuint majorVersion, GLuint minorVersion
	) {
		this->windowWidth = windowWidth;
		this->windowHeight = windowHeight;
		this->majorVersion = majorVersion;
		this->minorVersion = minorVersion;
		this->mainWindow = nullptr;
		this->bufferWidth = 0;
		this->bufferHeight = 0;
	}

	Window::~Window() {
		if (mainWindow) {
			glfwDestroyWindow(mainWindow);
		}

		glfwTerminate();
	}

	bool Window::setupWindow() {
		if (!glfwInit()) {
			NOVA_ERROR("Failed to initialize the window");
			return false;
		}

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
		windowWidth = vidMode->width;
		windowHeight = vidMode->height;

		NOVA_WARN("OpenGL Version: 4.6");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		glfwWindowHint(GLFW_RED_BITS, vidMode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, vidMode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, vidMode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, vidMode->refreshRate);

		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		mainWindow = glfwCreateWindow(
			windowWidth,
			windowHeight,
			"Nova Engine",
			nullptr,
			nullptr
		);

		if (!mainWindow) {
			NOVA_ERROR("Failed to create main window");
			return false;
		}

		NOVA_ASSERT(mainWindow != nullptr, "Main window cannot be null");

		glfwMakeContextCurrent(mainWindow);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			NOVA_ERROR("Failed to initialize main window");
			glfwDestroyWindow(mainWindow);
			glfwTerminate();

			return false;
		}

		glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

		if (bufferWidth == 0 || bufferHeight == 0) {
			glViewport(0, 0, windowWidth, windowHeight);
		}
		else {
			glViewport(0, 0, bufferWidth, bufferHeight);
		}

		glEnable(GL_DEPTH_TEST);
		createCallbacks();
		glfwSwapInterval(1);
		glfwSetWindowUserPointer(mainWindow, this);

		return true;
	}

	bool Window::windowShouldClose() {
		return glfwWindowShouldClose(mainWindow);
	}

	void Window::update(glm::vec4 clearColor) {
		glfwPollEvents();

		GLdouble currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		for (int idx = 0; idx < GLFW_KEY_LAST; idx++) {
			keys[idx] = glfwGetKey(mainWindow, idx) == GLFW_PRESS;
		}

		KeyStateEvent keyStateEvent(keys, deltaTime);
		EventBus::getInstance().dispatch(keyStateEvent);

		if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(mainWindow, GL_TRUE);
		}

		glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Window::swap() {
		glfwSwapBuffers(mainWindow);
	}

	void Window::createCallbacks() {
		glfwSetKeyCallback(mainWindow, handleKeys);
		glfwSetCursorPosCallback(mainWindow, handleMouse);
		glfwSetFramebufferSizeCallback(mainWindow, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);

			Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
			win->setWindowWidth(width);
			win->setWindowHeight(height);
			
			WindowResizeEvent resizeEvent(width, height);
			EventBus::getInstance().dispatch(resizeEvent);
			
			win->update(glm::vec4(0.1, 0.1, 0.1, 1.0));
		});
		glfwSetMouseButtonCallback(mainWindow, handleMouseButton);
	}

	void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
		Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		if (key >= 0 && key < 1024) {
			if (action == GLFW_PRESS) {
				KeyPressedEvent keyPressedEvent(key, 1);
				EventBus::getInstance().dispatch(keyPressedEvent);
			}
			else if (action == GLFW_RELEASE) {
				KeyReleasedEvent keyReleasedEvent(key);
				EventBus::getInstance().dispatch(keyReleasedEvent);
			}
		}
	}

	void Window::handleMouse(GLFWwindow* window, double xPos, double yPos) {
		Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

		if (currentWindow->mouseFirstMoved) {
			currentWindow->lastX = static_cast<GLfloat>(xPos);
			currentWindow->lastY = static_cast<GLfloat>(yPos);
			currentWindow->mouseFirstMoved = false;

			MouseMovedEvent mouseMovedEvent(xPos, yPos, currentWindow->keys);
			EventBus::getInstance().dispatch(mouseMovedEvent);
		}
		else {
			currentWindow->xChange = static_cast<GLfloat>(xPos - currentWindow->lastX);
			currentWindow->yChange = static_cast<GLfloat>(currentWindow->lastY - yPos);

			currentWindow->lastX = static_cast<GLfloat>(xPos);
			currentWindow->lastY = static_cast<GLfloat>(yPos);

			MouseMovedEvent mouseMovedEvent(currentWindow->xChange, currentWindow->yChange, currentWindow->keys);
			EventBus::getInstance().dispatch(mouseMovedEvent);
		}
	}

	void Window::handleMouseButton(GLFWwindow* window, int button, int action, int mods) {
		Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	}

	void Window::handleScroll(GLFWwindow* window, double xOffset, double yOffset) {
		Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	}

	GLfloat Window::getXChange() {
		GLfloat change = xChange;
		xChange = 0.0f;

		return change;
	}

	GLfloat Window::getYChange() {
		GLfloat change = yChange;
		yChange = 0.0f;

		return change;
	}

	GLFWwindow* Window::getWindowObject() {
		return mainWindow;
	}

	int Window::getWindowWidth() {
		return windowWidth;
	}

	int Window::getWindowHeight() {
		return windowHeight;
	}

	void Window::setWindowWidth(int newWidth) {
		windowWidth = newWidth;
	}

	void Window::setWindowHeight(int newHeight) {
		windowHeight = newHeight;
	}

	GLdouble Window::getDeltaTime() {
		return deltaTime;
	}
}