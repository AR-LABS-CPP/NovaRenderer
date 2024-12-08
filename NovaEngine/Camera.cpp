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
		projectionMatrix(glm::mat4(1.0)), cameraPos(cameraPos),cameraFront(cameraFront), cameraUp(cameraUp) {}

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
		projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, 0.1f, 100.0f);
	}

	void Camera::processKeyboard(bool* keys, GLfloat deltaTime) {
		GLfloat velocity = movementSpeed * deltaTime;

		if (keys[GLFW_KEY_LEFT_CONTROL]) {
			if (keys[GLFW_KEY_W]) cameraPos += cameraFront * velocity;
			if (keys[GLFW_KEY_S]) cameraPos -= cameraFront * velocity;
			if (keys[GLFW_KEY_A]) cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
			if (keys[GLFW_KEY_D]) cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
			if (keys[GLFW_KEY_SPACE]) cameraPos += cameraUp * velocity;
			if (keys[GLFW_KEY_LEFT_SHIFT]) cameraPos -= cameraUp * velocity;
		}
	}

	void Camera::processMouse(bool* keys, GLfloat xPos, GLfloat yPos) {
		if (keys[GLFW_KEY_LEFT_CONTROL]) {
			if (firstMouse) {
				lastX = windowWidth / 2.0;
				lastY = windowHeight / 2.0;

				firstMouse = false;
			}

			lastX = static_cast<GLfloat>(xPos);
			lastY = static_cast<GLfloat>(yPos);

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

			projectionMatrix = glm::perspective(glm::radians(fieldOfView), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
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
}