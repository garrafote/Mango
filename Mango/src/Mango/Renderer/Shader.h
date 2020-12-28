#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Mango {

	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

		virtual void UploadUniform(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void UploadUniform(const std::string& name, const glm::vec4& values) = 0;
	private:
		uint32_t m_RendererID;
	};
}
