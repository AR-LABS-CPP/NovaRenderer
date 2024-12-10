#include "pch.h"
#include "Gizmo.h"

namespace Nova {
	Gizmo::Gizmo(const Shader& shader)
		: shader(shader), modelMatrix(glm::mat4(1.0f)), isInteracting(false),
		selectedAxis(-1), axisScale(1.0f) {
		// X, Y, Z
		axisColors[0] = glm::vec3(1.0f, 0.0f, 0.0f); 
		axisColors[1] = glm::vec3(0.0f, 1.0f, 0.0f);
		axisColors[2] = glm::vec3(0.0f, 0.0f, 1.0f);
	}

	void Gizmo::initialize() {
		float axisVertices[] = {
			// X
			0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // origin
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // X+

			// Y
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // origin
			0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Y+

			// Z
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // origin
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f  // X+
		};

		glGenVertexArrays(1, &gizmoVAO);
		glGenBuffers(1, &gizmoVBO);

		glBindVertexArray(gizmoVAO);
		glBindBuffer(GL_ARRAY_BUFFER, gizmoVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}
	
	void Gizmo::render(
		const glm::mat4& model,
		const glm::mat4& view,
		const glm::mat4& projectiom
	) {
		shader.useShader();
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projectiom);

		for (int idx = 0; idx < 3; idx++) {
			shader.setVec3("gizmoColor", axisColors[idx]);
			glBindVertexArray(gizmoVAO);
			glDrawArrays(GL_LINES, idx * 2, 2);
		}

		glBindVertexArray(0);
	}
	
	void Gizmo::update(GLFWwindow* window, float deltaTime) {
		if (isInteracting) {
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);
			mouseY = 1080 - mouseY;

			glm::vec3 mousePos(mouseX, mouseY, 1.0f);
			float scaleFactor = mousePos.x - interactionStart.x;

			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f + scaleFactor * 0.1f));
		}
	}
	
	void Gizmo::setColor(const glm::vec3& color) {
		axisColors[0] = color;
		axisColors[1] = color;
		axisColors[2] = color;
	}
	
	void Gizmo::setModelMatrix(const glm::mat4& matrix) {
		modelMatrix = matrix;
	}
	
	void Gizmo::resetTransformation() {
		modelMatrix = glm::mat4(1.0f);
		axisScale = 1.0f;
	}

	bool Gizmo::rayIntersectsAxis(
		const glm::vec3& rayOrigin,
		const glm::vec3& rayDir,
		int axis,
		float& t
	) {
		glm::vec3 axisStart = glm::vec3(0.0f);
		glm::vec3 axisEnd = glm::vec3(0.0f);

		if (axis == 0) {
			axisEnd = glm::vec3(1.0f, 0.0f, 0.0f);
		}

		if (axis == 1) {
			axisEnd = glm::vec3(0.0f, 1.0f, 0.f);
		}

		if (axis == 2) {
			axisEnd = glm::vec3(0.0f, 0.0f, 1.0f);
		}

		return false;
	}
}