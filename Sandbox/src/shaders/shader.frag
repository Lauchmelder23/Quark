#version 460 core

layout(location = 0) in vec3 o_Position;
layout(location = 0) out vec4 color;

void main()
{
	color = vec4(o_Position, 1.0);
}