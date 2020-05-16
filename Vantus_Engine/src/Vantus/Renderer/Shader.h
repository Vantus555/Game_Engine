#pragma once
#include "string"
#include "glm/glm.hpp"

namespace Vantus {

	class Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploarUnformFloat4(const std::string& name, const glm::vec4& values);
		void UploarUnformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererID;
	};

}