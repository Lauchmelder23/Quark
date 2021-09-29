#version 460 core

layout(location = 0) in vec3 o_Color;
layout(location = 0) out vec4 color;

void main()
{
	color = vec4(o_Color, 1.0);
}