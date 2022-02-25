#pragma once

#include <string>

#include <Quark/Core.hpp>

QK_PHOTON_BEGIN

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D :
		public Texture
	{
	public:
		static Reference<Texture2D> Create(const std::string& path);
	};

QK_PHOTON_END
