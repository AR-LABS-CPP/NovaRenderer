#pragma once

#include "Renderer/Shader.h"
#include "Mesh.h"
#include "Model.h"

namespace Nova {
	class Gizmo {
	public:
		Shader shader;

		GLuint gizmoVAO, gizmoVBO;
		glm::vec3 axisColors[3];
		glm::mat4 modelMatrix;

		bool isInteracting;
		glm::vec3 interactionStart;
		int selectedAxis;

		glm::vec3 rayOrigin, rayDir;

		float axisScale;

		Gizmo() = default;
		Gizmo(const Shader& shader);

		void initialize();
		void render(
			const glm::mat4& model,
			const glm::mat4& view,
			const glm::mat4& projectiom
		);
		void setColor(const glm::vec3& color);
		void update(GLFWwindow* window, float deltaTime);
		void setModelMatrix(const glm::mat4& matrix);
		void resetTransformation();

		bool rayIntersectsAxis(
			const glm::vec3& rayOrigin,
			const glm::vec3& rayDir,
			int axis,
			float& t
		);		
	};
}