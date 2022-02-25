#pragma once

#include "RenderCommand.hpp"
#include <Quark/Photon/OrthographicCamera.hpp>
#include <Quark/Photon/Shader.hpp>

QK_PHOTON_BEGIN

	/**
	* @brief Structure for setting up scenes and submitting data/objects to that scene
	*/
	class Renderer
	{
	public:
		/**
		 * @brief Initializes the renderer and sets up API properties
		 */
		static void Init();

		/**
		 * @brief Tells the renderer to start a new scene with the given properties
		 * 
		 * @param camera The camera the scene should be rendered with
		 */
		static void BeginScene(OrthographicCamera& camera);

		/**
		 * @brief Ends the current scene
		 */
		static void EndScene();

		/**
		 * @brief Renders a VAO with a given shader and transformation in the current active scene
		 * 
		 * @param shader The shader to use when rendering the VAO
		 * @param vertexArray The VAO to render
		 * @param transform The transformations to apply to the object
		 */
		static void Submit(const Reference<Shader>& shader, const Reference<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

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