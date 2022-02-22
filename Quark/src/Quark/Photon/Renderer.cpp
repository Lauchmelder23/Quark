#include "qkpch.hpp"
#include "Renderer.hpp"

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

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->SetUniformMat4("u_ViewProjection", m_SceneProperties->ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

QK_PHOTON_END