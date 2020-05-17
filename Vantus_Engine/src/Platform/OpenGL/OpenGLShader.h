#pragma once
#include "Vantus/Renderer/Shader.h"
#include "string"
#include "glm/glm.hpp"

namespace Vantus {

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override; 

		void UploarUniformInt(const std::string& name, const int& value);

		void UploarUniformFloat(const std::string& name, const float& value);
		void UploarUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploarUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploarUniformFloat4(const std::string& name, const glm::vec4& values);

		void UploarUnformMat3(const std::string& name, const glm::mat3& matrix);
		void UploarUnformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererID;
	};

}