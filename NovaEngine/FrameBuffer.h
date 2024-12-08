#pragma once

#include "Log.h"

namespace Nova {
	class FrameBuffer {
	public:
		FrameBuffer(GLfloat width, GLfloat height);
		~FrameBuffer();

		GLuint getTexture();

		void rescaleFrameBuffer(GLfloat width, GLfloat height);
		void bindBuffer(GLfloat width, GLfloat height);
		void unbindBuffer() const;

	private:
		GLuint FBO, RBO, Texture;
	};
}