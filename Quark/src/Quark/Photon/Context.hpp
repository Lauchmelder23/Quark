#pragma once

namespace Quark 
{
	namespace Photon
	{
		class Context
		{
		public:
			virtual void Init() = 0;
			virtual void SwapBuffers() = 0;
		};
	}
}