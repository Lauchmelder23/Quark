#include "qkpch.hpp"
#include "RenderCommand.hpp"

#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

QK_PHOTON_BEGIN

	RendererAPI* RenderCommand::s_API = new OpenGLRendererAPI;

QK_PHOTON_END