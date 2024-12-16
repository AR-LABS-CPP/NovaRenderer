#include "pch.h"
#include "Camera.h"

namespace Nova {
	Camera::Camera(
		GLfloat yaw,
		GLfloat pitch,
		GLfloat lastX,
		GLfloat lastY,
		GLfloat sensitivity,
		GLfloat movementSpeed,
		GLfloat fieldOfView,
		GLfloat aspectRatio,
		GLfloat windowWidth,
		GLfloat windowHeight,
		glm::vec3 cameraPos,
		glm::vec3 cameraFront,
		glm::vec3 cameraUp
	) : yaw(yaw), pitch(pitch), lastX(lastX), lastY(lastY), sensitivity(sensitivity), movementSpeed(movementSpeed),
		fieldOfView(fieldOfView), aspectRatio(aspectRatio), windowWidth(windowWidth), windowHeight(windowHeight),
		projectionMatrix(glm::mat4(1.0)), cameraPos(cameraPos),cameraFront(cameraFront), cameraUp(cameraUp),
		nearClip(0.1), farClip(100000.0f) {
		subscribeToEvents();
	}

	void Camera::toggleFirstMouse() {
		if (firstMouse) {
			firstMouse = false;
			return;
		}

		firstMouse = true;
	}

	void Camera::setSpeed(GLfloat newMovementSpeed) {
		movementSpeed = newMovementSpeed;
	}

	void Camera::setSensitivity(GLfloat newSensitivity) {
		sensitivity = newSensitivity;
	}

	void Camera::setAspectRatio(GLfloat newAspectRatio) {
		aspectRatio = newAspectRatio;
		projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearClip, farClip);
	}

	void Camera::processKeyboard(KeyStateEvent& event) {
		GLfloat velocity = movementSpeed * event.getDeltaTime();

		bool* keys = event.getKeys();

		if (keys[GLFW_KEY_LEFT_CONTROL]) {
			if (keys[GLFW_KEY_W]) cameraPos += cameraFront * velocity;
			if (keys[GLFW_KEY_S]) cameraPos -= cameraFront * velocity;
			if (keys[GLFW_KEY_A]) cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
			if (keys[GLFW_KEY_D]) cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
			if (keys[GLFW_KEY_SPACE]) cameraPos += cameraUp * velocity;
			if (keys[GLFW_KEY_LEFT_SHIFT]) cameraPos -= cameraUp * velocity;
		}
	}

	void Camera::processMouse(MouseMovedEvent& event) {
		bool* keys = event.getKeys();

		if (keys[GLFW_KEY_LEFT_CONTROL]) {
			if (firstMouse) {
				lastX = windowWidth / 2.0;
				lastY = windowHeight / 2.0;

				firstMouse = false;
			}

			lastX = static_cast<GLfloat>(event.GetX());
			lastY = static_cast<GLfloat>(event.GetY());

			lastX *= sensitivity;
			lastY *= sensitivity;

			yaw += lastX;
			pitch += lastY;

			clampPitch();

			updateCameraLookAt();
		}
	}

	void Camera::orbit(GLfloat xChange, GLfloat yChange) {
		xChange *= sensitivity;
		yChange *= sensitivity;

		yaw += xChange;
		pitch -= yChange;

		clampPitch();
		updateCameraLookAt();
	}

	void Camera::pan(GLfloat xChange, GLfloat yChange) {
		glm::vec3 right = glm::normalize(glm::cross(cameraFront, cameraUp));
		cameraPos -= right * xChange * sensitivity;
		cameraPos += cameraUp * yChange * sensitivity;
	}
	
	void Camera::zoom(GLfloat yChange) {
		fieldOfView -= yChange * sensitivity;
		
		if (fieldOfView < 1.0f) {
			fieldOfView = 1.0f;
		}

		if (fieldOfView > 45.0) {
			fieldOfView = 45.0f;
		}
	}

	glm::mat4 Camera::getViewMatrix() {
		return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	glm::mat4 Camera::getProjectionMatrix() {
		if (!projectionMatrixInit) {
			projectionMatrixInit = true;

			projectionMatrix = glm::perspective(glm::radians(fieldOfView), (float)windowWidth / (float)windowHeight, nearClip, farClip);
			return projectionMatrix;
		}

		return projectionMatrix;
	}

	glm::vec3 Camera::getCameraPosition() {
		return cameraPos;
	}

	glm::vec3 Camera::getCameraFront() {
		return cameraFront;
	}

	void Camera::clampPitch() {
		if (pitch > 89.0f) {
			pitch = 89.0f;
		}
		else if (pitch < -89.0f) {
			pitch = -89.0f;
		}
	}

	void Camera::updateCameraLookAt() {
		glm::vec3 front;
		front.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
		front.y = std::sin(glm::radians(pitch));
		front.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));

		cameraFront = glm::normalize(front);
	}

	void Camera::subscribeToEvents() {
		eventQueue.subscribe<KeyStateEvent>([this](Event& event) {
			auto& keyStateEvent = static_cast<KeyStateEvent&>(event);
			processKeyboard(keyStateEvent);
		});

		eventQueue.subscribe<MouseMovedEvent>([this](Event& event) {
			auto& mouseMovedState = static_cast<MouseMovedEvent&>(event);
			processMouse(mouseMovedState);
		});

		eventQueue.subscribe<CameraFieldOfViewChangedEvent>([this](Event& event) {
			onFieldOfViewChanged(event);
		});

		eventQueue.subscribe<CameraNearClipChangedEvent>([this](Event& event) {
			onNearClipChanged(event);
		});

		eventQueue.subscribe<CameraFarClipChangedEvent>([this](Event& event) {
			onFarClipChanged(event);
		});

		eventQueue.subscribe<CameraMovementSpeedChangedEvent>([this](Event& event) {
			onMovementSpeedChanged(event);
		});
	}
}