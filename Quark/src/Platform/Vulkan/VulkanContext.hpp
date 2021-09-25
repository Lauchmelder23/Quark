#pragma once

#include "Quark/Photon/Context.hpp"

#include <vulkan/vulkan.h>

struct GLFWwindow;

namespace Quark
{
	namespace Photon
	{
		/**
		 * @brief Contains indices of Vulkan queue families
		 */
		struct QueueFamilyIndices
		{
			std::optional<uint32_t> GraphicsFamily;
			std::optional<uint32_t> PresentFamily;

			bool IsComplete() {
				return GraphicsFamily.has_value() && PresentFamily.has_value();
			}
		};

		/**
		 * @brief Abstraction of a Vulkan rendering context
		 */
		class QUARK_API VulkanContext : public Context
		{
		public:
			/**
			 * @brief        Creates a new context but doesn't initialize it.
			 *
			 * @param handle A pointer to the window API, in this case GLFW
			 */
			VulkanContext(GLFWwindow* handle);

			/**
			 * @brief Destroys the Vulkan instance
			 */
			~VulkanContext();

			/**
			 * @brief Initialize a new Vulkan context and make it current.
			 */
			void Init() override;

			/**
			 * @brief Swap the contexts frame buffers
			 */
			void SwapBuffers() override;

		private:
			void CreateInstance();
			void CreateSurface();
			void FindPhysicalDevice();
			void CreateLogicalDevice();

			bool IsDeviceSuitable(VkPhysicalDevice device);
			QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

		private:
			GLFWwindow*			m_Handle;
			VkSurfaceKHR		m_Surface;
			
			VkInstance			m_Instance;
			VkPhysicalDevice	m_PhysicalDevice;
			VkDevice			m_Device;
			VkQueue				m_GraphicsQueue;
			VkQueue				m_PresentQueue;
		};
	}
}