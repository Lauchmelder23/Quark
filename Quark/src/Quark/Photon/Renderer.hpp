#pragma once

#include "RenderCommand.hpp"

QK_PHOTON_BEGIN

	/**
	* @brief Renderer structure for doing/storing generic render API actions/data
	*/
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

	public:
		/**
		* @brief   Retrieve the currently used renderer API
		* 
		* @returns The current active API
		*/
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
	};

QK_PHOTON_END