#include "qkpch.hpp"
#include "VulkanContext.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Quark
{
	namespace Photon
	{
		VulkanContext::VulkanContext(GLFWwindow* handle) :
			m_Handle(handle), m_Surface(VK_NULL_HANDLE),
			m_Instance(VK_NULL_HANDLE), m_PhysicalDevice(VK_NULL_HANDLE), m_Device(VK_NULL_HANDLE), 
			m_GraphicsQueue(VK_NULL_HANDLE), m_PresentQueue(VK_NULL_HANDLE)
		{
		}

		VulkanContext::~VulkanContext()
		{
			vkDestroyDevice(m_Device, nullptr);
			vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
			vkDestroyInstance(m_Instance, nullptr);
		}

		void VulkanContext::Init()
		{
			int result = glfwVulkanSupported();
			QK_CORE_ASSERT(result, "Vulkan is not supported");

			CreateInstance();
			CreateSurface();
			FindPhysicalDevice();
			CreateLogicalDevice();
		}

		void VulkanContext::SwapBuffers()
		{
			
		}
		
		void VulkanContext::CreateInstance()
		{
			VkApplicationInfo appInfo{};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Vulkan App";
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName = "Quark";
			appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
			appInfo.apiVersion = VK_API_VERSION_1_0;

			VkInstanceCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = &appInfo;

			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions;

			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			createInfo.enabledExtensionCount = glfwExtensionCount;
			createInfo.ppEnabledExtensionNames = glfwExtensions;
			createInfo.enabledLayerCount = 0;

			VkResult result = vkCreateInstance(&createInfo, nullptr, &m_Instance);
			QK_CORE_ASSERT(result == VkResult::VK_SUCCESS, "Failed to create Vulkan instance.");
		}

		void VulkanContext::CreateSurface()
		{
			if (glfwCreateWindowSurface(m_Instance, m_Handle, nullptr, &m_Surface) != VK_SUCCESS)
			{
				QK_CORE_FATAL("Failed to create window surface!");
				throw std::runtime_error("");
			}
		}

		void VulkanContext::FindPhysicalDevice()
		{
			uint32_t deviceCount = 0;
			vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

			if (deviceCount == 0)
			{
				QK_CORE_FATAL("No GPUs with Vulkan support found.");
				throw std::runtime_error("");
			}

			std::vector<VkPhysicalDevice> devices(deviceCount);
			vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

			for (const VkPhysicalDevice& device : devices)
			{
				if (IsDeviceSuitable(device)) 
				{
					m_PhysicalDevice = device;
					break;
				}
			}

			if (m_PhysicalDevice == VK_NULL_HANDLE)
			{
				QK_CORE_FATAL("No suitable GPU found.");
				throw std::runtime_error("");
			}

			std::stringstream ss;
			ss << "Found the following GPUs: " << std::endl;

			VkPhysicalDeviceProperties deviceProp;
			for (const VkPhysicalDevice& device : devices)
			{
				 vkGetPhysicalDeviceProperties(device, &deviceProp);
				 ss << "\t" << ((device == m_PhysicalDevice) ? "> " : "  ") << deviceProp.deviceName << std::endl;
			}
			QK_CORE_INFO(ss.str());

		}

		void VulkanContext::CreateLogicalDevice()
		{
			QueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);

			std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
			std::set<uint32_t> uniqueQueueFamilies = { indices.GraphicsFamily.value(), indices.PresentFamily.value() };

			float queuePriority = 1.0f;
			for (uint32_t queueFamily : uniqueQueueFamilies)
			{
				VkDeviceQueueCreateInfo queueCreateInfo{};
				queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueCreateInfo.queueFamilyIndex = indices.GraphicsFamily.value();
				queueCreateInfo.queueCount = 1;
				queueCreateInfo.pQueuePriorities = &queuePriority;

				queueCreateInfos.push_back(queueCreateInfo);
			}

			VkPhysicalDeviceFeatures deviceFeatures{};
		
			VkDeviceCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			createInfo.pQueueCreateInfos = queueCreateInfos.data();
			createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
			createInfo.pEnabledFeatures = &deviceFeatures;
			createInfo.enabledExtensionCount = 0;
			createInfo.enabledLayerCount = 0;

			if (vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_Device) != VK_SUCCESS)
			{
				QK_CORE_FATAL("Failed to create logical device.");
				throw std::runtime_error("");
			}

			vkGetDeviceQueue(m_Device, indices.GraphicsFamily.value(), 0, &m_GraphicsQueue);
			vkGetDeviceQueue(m_Device, indices.PresentFamily.value(), 0, &m_PresentQueue);	
		}

		QueueFamilyIndices VulkanContext::FindQueueFamilies(VkPhysicalDevice device)
		{
			QueueFamilyIndices indices;

			uint32_t queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

			std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

			int i = 0;
			for (const VkQueueFamilyProperties& queueFamily : queueFamilies) {
				if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
					indices.GraphicsFamily = i;
				}

				VkBool32 presentSupport = false;
				vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_Surface, &presentSupport);
				if (presentSupport)
					indices.PresentFamily = i;

				if (indices.IsComplete())
					break;

				i++;
			}

			

			return indices;
		}

		bool VulkanContext::IsDeviceSuitable(VkPhysicalDevice device)
		{
			QueueFamilyIndices indices = FindQueueFamilies(device);

			return indices.IsComplete();
		}
	}
}