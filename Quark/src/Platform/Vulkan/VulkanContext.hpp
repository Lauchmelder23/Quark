#pragma once

#include "Quark/Photon/Context.hpp"

#include <map>
#include <vulkan/vulkan.h>

struct GLFWwindow;

namespace Quark
{
	namespace Photon
	{
		/**
		 * @brief Abstraction of a Vulkan rendering context
		 */
		class QUARK_API VulkanContext : public Context
		{
			struct QueueFamilyIndices
			{
				std::optional<uint32_t> Graphics;
				std::optional<uint32_t> Present;

				bool Complete()
				{
					return Graphics.has_value() && Present.has_value();
				}
			};

			struct SwapChainSupportDetails
			{
				VkSurfaceCapabilitiesKHR Capabilities;
				std::vector<VkSurfaceFormatKHR> Format;
				std::vector<VkPresentModeKHR> PresentModes;
			};

		public:
			/**
			 * @brief A map of Vulkan error messages
			 */
			static const std::map<VkResult, std::string> VulkanErrorStrings; 

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
			void FindPhysicalDevices();
			void CreateLogicalDevice();
			void CreateSurface();
			void CreateSwapChain();
			void CreateImageViews();
			void CreateSemaphores();

			bool IsDeviceSuitable(VkPhysicalDevice device);
			bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
			QueueFamilyIndices GetQueueFamilyIndices(VkPhysicalDevice device);
			SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

			VkSurfaceFormatKHR	ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			VkPresentModeKHR	ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
			VkExtent2D			ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		private:
			GLFWwindow*					m_Handle;
			VkInstance					m_Instance;
			VkSurfaceKHR				m_Surface;

			VkPhysicalDevice			m_PhysicalDevice;
			VkDevice					m_Device;
			VkQueue						m_GraphicsQueue;
			VkQueue						m_PresentQueue;

			VkSwapchainKHR				m_SwapChain;
			std::vector<VkImage>		m_SwapChainImages;
			std::vector<VkImageView>	m_SwapChainImageViews;
			std::vector<VkFramebuffer>	m_SwapChainFrameBuffers;
			VkFormat					m_SwapChainImageFormat;
			VkExtent2D					m_SwapChainExtent;

			VkSemaphore					m_ImageAvailableSemaphore;
			VkSemaphore					m_RenderFinishedSemaphore;
		};
	}
}