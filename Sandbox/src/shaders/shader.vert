#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;

layout(location = 0) out vec3 o_Color;

void main()
{
	o_Color = a_Color;
	gl_Position = vec4(a_Position, 1.0);
}