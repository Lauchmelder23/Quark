#pragma once

#include <string>
#include <vector>

namespace Quark
{
	namespace Photon
	{
		struct VertexShaderBinary
		{
			std::string OpenGL;
			std::vector<uint32_t> Vulkan;
		};

		struct FragmentShaderBinary
		{
			std::string OpenGL;
			std::vector<uint32_t> Vulkan;
		};
	}
}