#pragma once

#include "RenderCommand.hpp"
#include <Quark/Photon/OrthographicCamera.hpp>
#include <Quark/Photon/Shader.hpp>

QK_PHOTON_BEGIN

	/**
	* @brief Renderer structure for doing/storing generic render API actions/data
	*/
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		/**
		* @brief   Retrieve the currently used renderer API
		* 
		* @returns The current active API
		*/
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };

	private:
		struct SceneProperties
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneProperties* m_SceneProperties;
	};

QK_PHOTON_END