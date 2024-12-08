#pragma once

#include "Events/EventBus.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace Nova {
	class Camera {
	public:
		Camera(
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
			glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 3.0),
			glm::vec3 cameraFront = glm::vec3(0.0, 0.0, -1.0),
			glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0)
		);

		void toggleFirstMouse();
		void setSpeed(GLfloat newMovementSpeed);
		void setSensitivity(GLfloat newSensitivity);
		void setAspectRatio(GLfloat aspectratio);

		void processKeyboard(KeyStateEvent& event);
		void processMouse(MouseMovedEvent& event);

		void orbit(GLfloat xChange, GLfloat yChange);
		void pan(GLfloat xChange, GLfloat yChange);
		void zoom(GLfloat yChange);

		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();
		glm::vec3 getCameraPosition();
		glm::vec3 getCameraFront();

		void subscribeToEvents();
	private:
		GLboolean firstMouse = true;
		GLboolean projectionMatrixInit = false;
		GLfloat yaw, pitch, lastX, lastY, sensitivity, movementSpeed;
		GLfloat fieldOfView, aspectRatio, windowWidth, windowHeight;

		glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 3.0);
		glm::vec3 cameraFront = glm::vec3(0.0, 0.0, -1.0);
		glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);

		glm::mat4 projectionMatrix;

		void clampPitch();
		void updateCameraLookAt();
	};
}