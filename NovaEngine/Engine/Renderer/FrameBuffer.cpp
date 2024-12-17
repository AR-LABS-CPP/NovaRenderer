#include "pch.h"
#include "FrameBuffer.h"

namespace Nova {
	FrameBuffer::FrameBuffer(GLfloat width, GLfloat height) {
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		glGenTextures(1, &Texture);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Texture, 0);

		glGenRenderbuffers(1, &RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

		NOVA_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
			"Framebuffer must be complete");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
	
	FrameBuffer::~FrameBuffer() {
		glDeleteFramebuffers(1, &FBO);
		glDeleteTextures(1, &Texture);
		glDeleteRenderbuffers(1, &RBO);

		if (DepthMapFBO) {
			glDeleteFramebuffers(1, &DepthMapFBO);
			glDeleteTextures(1, &DepthMapTexture);
		}
	}

	GLuint FrameBuffer::getTexture() {
		return Texture;
	}

	GLuint FrameBuffer::getDepthMapTexture() {
		return DepthMapTexture;
	}

	void FrameBuffer::rescaleFrameBuffer(GLfloat width, GLfloat height) {
		glBindTexture(GL_TEXTURE_2D, Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Texture, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

		NOVA_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, 
			"Fame buffer must be complete before rendering resized frame");

		glViewport(0, 0, width, height);
	}
	
	void FrameBuffer::bindBuffer(GLfloat width, GLfloat height) {
		rescaleFrameBuffer(width, height);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void FrameBuffer::unbindBuffer() const {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::unbindDepthMapBuffer() const {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::initDepthMapBuffer(GLfloat width, GLfloat height) {
		glGenFramebuffers(1, &DepthMapFBO);
		glGenTextures(1, &DepthMapTexture);

		glBindTexture(GL_TEXTURE_2D, DepthMapTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glBindFramebuffer(GL_FRAMEBUFFER, DepthMapFBO);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, depthMapBorderColor);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthMapTexture, 0);
		
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			NOVA_ERROR("Depth map framebuffer is incomplete.");
		}
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::bindDepthMapBuffer(GLfloat width, GLfloat height) {
		glViewport(0, 0, width, height);
		glBindFramebuffer(GL_FRAMEBUFFER, DepthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, DepthMapTexture);
	}
}