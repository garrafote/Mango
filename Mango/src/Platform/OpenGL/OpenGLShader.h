#pragma once

#include "Mango/Renderer/Shader.h"

namespace Mango {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniform(const std::string& name, const glm::mat4& matrix) override;

	private:
		uint32_t m_RendererID;
	};
}
