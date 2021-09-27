#include "ShaderBinaries.hpp"

const Quark::Photon::VertexShaderBinary SandboxShaders::vertexShader = {R"(#version core 330

layout(location = 0) vec3 vertex;

void main()
{

})"};

const Quark::Photon::FragmentShaderBinary SandboxShaders::fragmentShader = {R"(This is a cool fragment shader!

lol test)"};
