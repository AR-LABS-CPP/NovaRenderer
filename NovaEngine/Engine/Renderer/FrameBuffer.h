#pragma once

#include "Log/Log.h"

namespace Nova {
	class FrameBuffer {
	public:
		FrameBuffer(GLfloat width, GLfloat height);
		~FrameBuffer();

		GLuint getTexture();
		GLuint getDepthMapTexture();

		void rescaleFrameBuffer(GLfloat width, GLfloat height);
		void bindBuffer(GLfloat width, GLfloat height);
		void initDepthMapBuffer(GLfloat width, GLfloat height);
		void bindDepthMapBuffer(GLfloat width, GLfloat height);
		void unbindBuffer() const;
		void unbindDepthMapBuffer() const;
	public:
		GLuint FBO = 0, RBO = 0, Texture = 0;
		GLuint DepthMapFBO = 0, DepthMapTexture = 0;
		GLfloat depthMapBorderColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	};
}