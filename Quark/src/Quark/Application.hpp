#pragma once

#include "Core.hpp"
#include "Events/Event.hpp"

namespace Quark
{
	class QUARK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in the client
	Application* CreateApplication();

}