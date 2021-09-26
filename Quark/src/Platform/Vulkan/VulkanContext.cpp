#include "qkpch.hpp"
#include "VulkanContext.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define QK_VULKAN_ASSERT(condition, message) if((condition) != VK_SUCCESS) throw std::runtime_error(message + std::string(": ") + VulkanErrorStrings.at(condition));

namespace Quark
{
	namespace Photon
	{
		const std::map<VkResult, std::string> VulkanContext::VulkanErrorStrings = {
			{VK_SUCCESS,									"Success"},
			{VK_NOT_READY,									"Fence or query has not yet completed"},
			{VK_TIMEOUT,									"Wait operation has not completed in the specified time"},
			{VK_EVENT_SET,									"Event is signaled"},
			{VK_EVENT_RESET,								"Event is unsignaled"},
			{VK_INCOMPLETE,									"Return array was too small for the result" },
			{VK_SUBOPTIMAL_KHR,								"Swapchain no longer matches the surface properties exactly"},
			{VK_THREAD_IDLE_KHR,							"Deferred operation is not complete but there is currently no work for this thread"},
			{VK_THREAD_DONE_KHR,							"Deferred operation is not complete but there is no work remaining for additional threads"},
			{VK_OPERATION_DEFERRED_KHR,						"Deferred operation was requested and at least some work was deferred"},
			{VK_OPERATION_NOT_DEFERRED_KHR,					"Deferred operation was requested and no operations were deferred"},
			{VK_PIPELINE_COMPILE_REQUIRED_EXT,				"Requested pipeline creation would have required compilation, but the application requested no compilation to be performed"},

			{VK_ERROR_OUT_OF_HOST_MEMORY,					"Host memory allocation failed"},
			{VK_ERROR_OUT_OF_DEVICE_MEMORY,					"Device memory allocation failed"},
			{VK_ERROR_INITIALIZATION_FAILED,				"Initialization of an object failed"},
			{VK_ERROR_DEVICE_LOST,							"Logical of physical device has been lost"},
			{VK_ERROR_MEMORY_MAP_FAILED,					"Mapping of memory object failed"},
			{VK_ERROR_LAYER_NOT_PRESENT,					"Requested layer is not present or could not be loaded"},
			{VK_ERROR_EXTENSION_NOT_PRESENT,				"Requested extension is not supported"},
			{VK_ERROR_FEATURE_NOT_PRESENT,					"Requested feature is not supported"},
			{VK_ERROR_INCOMPATIBLE_DRIVER,					"The requested version of Vulkan is not supported by the driver or is otherwise incompatible"},
			{VK_ERROR_TOO_MANY_OBJECTS,						"Too many objects of this type have already been created"},
			{VK_ERROR_FORMAT_NOT_SUPPORTED,					"Requested format is not supported on this device"},
			{VK_ERROR_FRAGMENTED_POOL,						"Pool allocation failed due to fragmentation of the pool's memory"},
			{VK_ERROR_SURFACE_LOST_KHR,						"Surface is no longer available"},
			{VK_ERROR_NATIVE_WINDOW_IN_USE_KHR,				"Requested window is already in use by Vulkan or another API and cannot be used again"},
			{VK_ERROR_OUT_OF_DATE_KHR,						"Surface changed in such a way that it is no longer compatible with the swapchain"},
			{VK_ERROR_INCOMPATIBLE_DISPLAY_KHR,				"The display used by the swapchain does not use the same presentable image layout or is incompatible"},
			{VK_ERROR_INVALID_SHADER_NV,					"Shader(s) failed to compile or link"},
			{VK_ERROR_OUT_OF_POOL_MEMORY,					"Pool memory allocation failed"},
			{VK_ERROR_INVALID_EXTERNAL_HANDLE,				"External handle is not a valid handle"},
			{VK_ERROR_FRAGMENTATION,						"Descriptor pool creation failed due to fragmentation"},
			{VK_ERROR_INVALID_DEVICE_ADDRESS_EXT,			"Buffer creation failed because the requested address is not available"},
			{VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS,		"Buffer creation or memory allocation failed because the requested address is unavailable"},
			{VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT,	"Operation on a swapchain failed as it did not have exclusive full-screen access"},
			{VK_ERROR_UNKNOWN,								"Unknown error"}
		};

		const std::vector<const char*> VALIDATION_LAYERS = {
			// "VK_LAYER_KHRONOS_validation",
			"VK_LAYER_LUNARG_monitor"
		};

		const std::vector<const char*> DEVICE_EXTENSIONS = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		VulkanContext::VulkanContext(GLFWwindow* handle) :
			m_Handle(handle), m_Instance(VK_NULL_HANDLE), m_Surface(VK_NULL_HANDLE),
			m_PhysicalDevice(VK_NULL_HANDLE), m_Device(VK_NULL_HANDLE),
			m_GraphicsQueue(VK_NULL_HANDLE), m_PresentQueue(VK_NULL_HANDLE),
			m_SwapChain(VK_NULL_HANDLE)
		{
		}

		VulkanContext::~VulkanContext()
		{
			vkDestroySemaphore(m_Device, m_RenderFinishedSemaphore, nullptr);
			vkDestroySemaphore(m_Device, m_ImageAvailableSemaphore, nullptr);

			for (const VkFramebuffer& framebuffer : m_SwapChainFrameBuffers)
				vkDestroyFramebuffer(m_Device, framebuffer, nullptr);

			for (const VkImageView& imageView : m_SwapChainImageViews)
				vkDestroyImageView(m_Device, imageView, nullptr);

			vkDestroySwapchainKHR(m_Device, m_SwapChain, nullptr);
			vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);

			vkDeviceWaitIdle(m_Device);
			vkDestroyDevice(m_Device, nullptr);

			vkDestroyInstance(m_Instance, nullptr);
		}

		void VulkanContext::Init()
		{
			int result = glfwVulkanSupported();
			QK_CORE_ASSERT(result, "Vulkan is not supported");

			CreateInstance();
			CreateSurface();
			FindPhysicalDevices();
			CreateLogicalDevice();
			CreateSwapChain();
			CreateImageViews();
			CreateSemaphores();
		}

		void VulkanContext::SwapBuffers()
		{
			uint32_t imageIndex;
			vkAcquireNextImageKHR(m_Device, m_SwapChain, UINT64_MAX, m_ImageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

			VkPresentInfoKHR presentInfo{};
			presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			
			VkSwapchainKHR swapChains[] = { m_SwapChain };
			presentInfo.swapchainCount = 1;
			presentInfo.pSwapchains = swapChains;
			presentInfo.pImageIndices = &imageIndex;

			vkQueuePresentKHR(m_PresentQueue, &presentInfo);
		}

		void VulkanContext::CreateInstance()
		{
			VkResult result;

			VkApplicationInfo appInfo{};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pNext = nullptr;
			appInfo.pApplicationName = "Quark Vulkan";
			appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
			appInfo.pEngineName = "Quark";
			appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
			appInfo.apiVersion = VK_API_VERSION_1_0;

			uint32_t numLayers;
			result = vkEnumerateInstanceLayerProperties(&numLayers, nullptr);
			QK_VULKAN_ASSERT(result, "Failed to enumerate instance layer properties");

			std::vector<VkLayerProperties> layerProperties;
			layerProperties.resize(numLayers);

			result = vkEnumerateInstanceLayerProperties(&numLayers, layerProperties.data());
			QK_VULKAN_ASSERT(result, "Failed to enumerate instance layer properties");

			std::vector<const char*> presentLayers;

			for (const char* layerName : VALIDATION_LAYERS)
			{
				bool layerFound = false;
				for (const VkLayerProperties& layerProperty : layerProperties)
				{
					if (strcmp(layerProperty.layerName, layerName))
					{
						presentLayers.push_back(layerName);
						layerFound = true;
						break;
					}
				}

				if (layerFound)
					QK_CORE_INFO("Activated validation layer \"{0}\"", layerName);
				else
					QK_CORE_WARN("Could not activate validation layer \"{0}\"", layerName);
			}

			uint32_t numExtensions;
			const char** extensions = glfwGetRequiredInstanceExtensions(&numExtensions);

			VkInstanceCreateInfo instanceCreateInfo{};
			instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instanceCreateInfo.pApplicationInfo = &appInfo;
			instanceCreateInfo.enabledLayerCount = presentLayers.size();
			instanceCreateInfo.ppEnabledLayerNames = presentLayers.data();
			instanceCreateInfo.enabledExtensionCount = numExtensions;
			instanceCreateInfo.ppEnabledExtensionNames = extensions;

			result = vkCreateInstance(&instanceCreateInfo, nullptr, &m_Instance);
			QK_VULKAN_ASSERT(result, "Failed to create Vulkan instance");

			QK_CORE_INFO("Vulkan instance created at {0}", fmt::ptr(&m_Instance));
		}

		void VulkanContext::FindPhysicalDevices()
		{
			VkResult result;

			uint32_t numDevices;
			result = vkEnumeratePhysicalDevices(m_Instance, &numDevices, nullptr);
			QK_VULKAN_ASSERT(result, "Physical device enumeration failed");

			std::vector<VkPhysicalDevice> physicalDevices;
			physicalDevices.resize(numDevices);

			result = vkEnumeratePhysicalDevices(m_Instance, &numDevices, physicalDevices.data());
			QK_VULKAN_ASSERT(result, "Physical device enumeration failed");

			for (const VkPhysicalDevice& physicalDevice : physicalDevices)
			{
				if (IsDeviceSuitable(physicalDevice))
				{
					m_PhysicalDevice = physicalDevice;
					break;
				}
			}

			if (m_PhysicalDevice == VK_NULL_HANDLE)
				throw std::runtime_error("Could not find a suitable physical device");

			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(m_PhysicalDevice, &deviceProperties);
			QK_CORE_INFO("Found physical device \"{0}\" at {1}", deviceProperties.deviceName, fmt::ptr(m_PhysicalDevice));
		}

		void VulkanContext::CreateLogicalDevice()
		{
			VkResult result;

			QueueFamilyIndices indices = GetQueueFamilyIndices(m_PhysicalDevice);

			if (!indices.Complete())
				throw std::runtime_error("Failed to find suitable queue families");

			std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
			std::set<uint32_t> uniqueQueueFamilies = { indices.Graphics.value(), indices.Present.value() };

			float priorities = 1.0f;
			for (uint32_t queueFamily : uniqueQueueFamilies)
			{
				VkDeviceQueueCreateInfo deviceQueueCreateInfo{};
				deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				deviceQueueCreateInfo.queueFamilyIndex = queueFamily;
				deviceQueueCreateInfo.queueCount = 1;
				deviceQueueCreateInfo.pQueuePriorities = &priorities;

				queueCreateInfos.push_back(deviceQueueCreateInfo);
			}

			VkPhysicalDeviceFeatures physicalDeviceFeatures{};

			VkDeviceCreateInfo deviceCreateInfo{};
			deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
			deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
			deviceCreateInfo.pEnabledFeatures = &physicalDeviceFeatures;
			deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(DEVICE_EXTENSIONS.size());
			deviceCreateInfo.ppEnabledExtensionNames = DEVICE_EXTENSIONS.data();

			result = vkCreateDevice(m_PhysicalDevice, &deviceCreateInfo, nullptr, &m_Device);
			QK_VULKAN_ASSERT(result, "Failed to create logical device");

			QK_CORE_INFO("Created logical device at {0}", fmt::ptr(m_Device));

			vkGetDeviceQueue(m_Device, indices.Graphics.value(), 0, &m_GraphicsQueue);
			vkGetDeviceQueue(m_Device, indices.Present.value(), 0, &m_PresentQueue);
		}

		void VulkanContext::CreateSurface()
		{
			VkResult result = glfwCreateWindowSurface(m_Instance, m_Handle, nullptr, &m_Surface);
			QK_VULKAN_ASSERT(result, "Failed to create window surface");

			QK_CORE_INFO("Created window surface at {0}", fmt::ptr(m_Surface));
		}

		void VulkanContext::CreateSwapChain()
		{
			SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(m_PhysicalDevice);

			VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.Format);
			VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.PresentModes);
			VkExtent2D extent = ChooseSwapExtent(swapChainSupport.Capabilities);

			uint32_t imageCount = swapChainSupport.Capabilities.minImageCount + 1;
			if (swapChainSupport.Capabilities.maxImageCount > 0 && imageCount > swapChainSupport.Capabilities.maxImageCount)
				imageCount = swapChainSupport.Capabilities.maxImageCount;

			VkSwapchainCreateInfoKHR createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			createInfo.surface = m_Surface;
			createInfo.minImageCount = imageCount;
			createInfo.imageColorSpace = surfaceFormat.colorSpace;
			createInfo.imageFormat = surfaceFormat.format;
			createInfo.imageExtent = extent;
			createInfo.imageArrayLayers = 1;
			createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

			QueueFamilyIndices indices = GetQueueFamilyIndices(m_PhysicalDevice);
			uint32_t queueFamilyIndices[] = { indices.Graphics.value(), indices.Present.value() };

			if (indices.Graphics != indices.Present)
			{
				createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
				createInfo.queueFamilyIndexCount = 2;
				createInfo.pQueueFamilyIndices = queueFamilyIndices;
			}
			else
			{
				createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
				createInfo.queueFamilyIndexCount = 0;
				createInfo.pQueueFamilyIndices = nullptr;
			}

			createInfo.preTransform = swapChainSupport.Capabilities.currentTransform;
			createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
			createInfo.presentMode = presentMode;
			createInfo.clipped = VK_TRUE;
			createInfo.oldSwapchain = VK_NULL_HANDLE;

			VkResult result = vkCreateSwapchainKHR(m_Device, &createInfo, nullptr, &m_SwapChain);
			QK_VULKAN_ASSERT(result, "Failed to create swap chain");

			QK_CORE_INFO("Created swapchain at {0}", fmt::ptr(m_SwapChain));

			uint32_t numImages;
			vkGetSwapchainImagesKHR(m_Device, m_SwapChain, &numImages, nullptr);
			m_SwapChainImages.resize(numImages);
			vkGetSwapchainImagesKHR(m_Device, m_SwapChain, &numImages, m_SwapChainImages.data());

			m_SwapChainImageFormat = surfaceFormat.format;
			m_SwapChainExtent = extent;
		}

		void VulkanContext::CreateImageViews()
		{
			m_SwapChainImageViews.resize(m_SwapChainImages.size());

			for (size_t i = 0; i < m_SwapChainImages.size(); i++)
			{
				VkImageViewCreateInfo createInfo{};
				createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				createInfo.image = m_SwapChainImages[i];
				createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
				createInfo.format = m_SwapChainImageFormat;
				createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
				createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
				createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
				createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
				createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				createInfo.subresourceRange.baseMipLevel = 0;
				createInfo.subresourceRange.levelCount = 1;
				createInfo.subresourceRange.baseArrayLayer = 0;
				createInfo.subresourceRange.layerCount = 1;

				VkResult result = vkCreateImageView(m_Device, &createInfo, nullptr, &m_SwapChainImageViews[i]);
				QK_VULKAN_ASSERT(result, "Failed to create image views");
			}

			QK_CORE_INFO("Created image views");
		}

		void VulkanContext::CreateSemaphores()
		{
			VkSemaphoreCreateInfo semaphoreInfo{};
			semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

			VkResult result = vkCreateSemaphore(m_Device, &semaphoreInfo, nullptr, &m_ImageAvailableSemaphore);
			QK_VULKAN_ASSERT(result, "Failed to create semaphore");

			result = vkCreateSemaphore(m_Device, &semaphoreInfo, nullptr, &m_RenderFinishedSemaphore);
			QK_VULKAN_ASSERT(result, "Failed to create semaphore");

			QK_CORE_INFO("Created semaphores");
		}

		bool VulkanContext::IsDeviceSuitable(VkPhysicalDevice device)
		{
			QueueFamilyIndices indices = GetQueueFamilyIndices(device);

			bool extensionsSupported = CheckDeviceExtensionSupport(device);

			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(device, &deviceProperties);

			VkPhysicalDeviceFeatures deviceFeatures;
			vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

			bool swapChainAdequate = false;
			if (extensionsSupported)
			{
				SwapChainSupportDetails swapChainSupportDetails = QuerySwapChainSupport(device);
				swapChainAdequate = !swapChainSupportDetails.Format.empty() && !swapChainSupportDetails.PresentModes.empty();
			}

			return (
				deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU		&&
				deviceFeatures.geometryShader											&&
				extensionsSupported														&&
				swapChainAdequate														&&
				indices.Complete()
			);
		}

		bool VulkanContext::CheckDeviceExtensionSupport(VkPhysicalDevice device)
		{
			uint32_t extensionCount;
			vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

			std::vector<VkExtensionProperties> extensionProperties;
			extensionProperties.resize(extensionCount);

			vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, extensionProperties.data());

			std::set<std::string> requiredExtensions(DEVICE_EXTENSIONS.begin(), DEVICE_EXTENSIONS.end());
			for (const VkExtensionProperties& extensionProperty : extensionProperties)
			{
				requiredExtensions.erase(extensionProperty.extensionName);
			}

			return requiredExtensions.empty();
		}

		VulkanContext::QueueFamilyIndices VulkanContext::GetQueueFamilyIndices(VkPhysicalDevice device)
		{
			QueueFamilyIndices indices;

			uint32_t numQueueFamilies;
			vkGetPhysicalDeviceQueueFamilyProperties(device, &numQueueFamilies, nullptr);

			std::vector<VkQueueFamilyProperties> queueFamilyProperties;
			queueFamilyProperties.resize(numQueueFamilies);
			vkGetPhysicalDeviceQueueFamilyProperties(device, &numQueueFamilies, queueFamilyProperties.data());

			uint32_t i = 0;
			for (const VkQueueFamilyProperties& queueFamilyProperty : queueFamilyProperties)
			{
				if (queueFamilyProperty.queueFlags & VK_QUEUE_GRAPHICS_BIT)
					indices.Graphics = i;

				VkBool32 presentSupport = false;
				vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_Surface, &presentSupport);
				if (presentSupport)
					indices.Present = i;

				i++;
			}

			return indices;
		}

		VulkanContext::SwapChainSupportDetails VulkanContext::QuerySwapChainSupport(VkPhysicalDevice device)
		{
			SwapChainSupportDetails details;

			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_Surface, &details.Capabilities);

			uint32_t numFormats;
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &numFormats, nullptr);
			
			if (numFormats != 0)
			{
				details.Format.resize(numFormats);
				vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &numFormats, details.Format.data());
			}

			uint32_t numPresentModes;
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &numPresentModes, nullptr);

			if (numPresentModes != 0)
			{
				details.PresentModes.resize(numPresentModes);
				vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &numPresentModes, details.PresentModes.data());
			}

			return details;
		}

		VkSurfaceFormatKHR VulkanContext::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
		{
			for (const VkSurfaceFormatKHR& availableFormat : availableFormats)
				if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
					return availableFormat;

			return availableFormats[0];
		}

		VkPresentModeKHR VulkanContext::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
		{
			for (const VkPresentModeKHR& availablePresentMode : availablePresentModes)
				if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
					return availablePresentMode;

			return VK_PRESENT_MODE_FIFO_KHR;
		}

		VkExtent2D VulkanContext::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
		{
			if (capabilities.currentExtent.width != UINT32_MAX)
			{
				return capabilities.currentExtent;
			}
			else
			{
				int width, height;
				glfwGetFramebufferSize(m_Handle, &width, &height);

				VkExtent2D actualExtent = {
					static_cast<uint32_t>(width),
					static_cast<uint32_t>(height)
				};

				actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
				actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);

				return actualExtent;
			}
		}
	}
}