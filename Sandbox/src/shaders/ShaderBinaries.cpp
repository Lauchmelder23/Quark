#include "ShaderBinaries.hpp"

const Quark::Photon::VertexShaderBinary SandboxVertexShaders::shader = {R"(#version 330 core

layout(location = 0) in vec3 a_Position;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
})"};

const Quark::Photon::FragmentShaderBinary SandboxFragmentShaders::shader = {R"(#version 330 core

out vec4 color;

void main()
{
	color = vec4(0.8, 0.5, 0.1, 1.0);
})"};
