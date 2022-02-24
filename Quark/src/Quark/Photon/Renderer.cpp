#include "qkpch.hpp"
#include "Renderer.hpp"
#include <Platform/OpenGL/OpenGLShader.hpp>

QK_PHOTON_BEGIN

	Renderer::SceneProperties* Renderer::m_SceneProperties = new Renderer::SceneProperties;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneProperties->ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{
		// Does nothing right now
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_ViewProjection", m_SceneProperties->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_Model", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

QK_PHOTON_END