#pragma once 

QK_PHOTON_BEGIN

	/**
	* An structure representing datatypes common in shading languages
	*/
	enum class ShaderDataType
	{
		Bool, Bool2, Bool3, Bool4,
		Int, Int2, Int3, Int4,
		Uint, Uint2, Uint3, Uint4,
		Float, Float2, Float3, Float4,
		Double, Double2, Double3, Double4,

		Mat2, Mat3, Mat4,
		Vec2 = Float2, Vec3 = Float3, Vec4 = Float4
	};

	/**
	* @brief      Retrieves the size of a shader datatype
	* 
	* @param type The type to calculate the size of
	* @retuens    The size of the type
	*/
	static size_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:	
		case ShaderDataType::Int:
		case ShaderDataType::Uint:
		case ShaderDataType::Float:
			return 4 * 1;

		case ShaderDataType::Bool2:
		case ShaderDataType::Int2:
		case ShaderDataType::Uint2:
		case ShaderDataType::Float2:
			return 4 * 2;

		case ShaderDataType::Bool3:
		case ShaderDataType::Int3:
		case ShaderDataType::Uint3:
		case ShaderDataType::Float3:
			return 4 * 3;

		case ShaderDataType::Bool4:
		case ShaderDataType::Int4:
		case ShaderDataType::Uint4:
		case ShaderDataType::Float4:
			return 4 * 4;

		case ShaderDataType::Double:	return 8 * 1;
		case ShaderDataType::Double2:	return 8 * 2;
		case ShaderDataType::Double3:	return 8 * 3;
		case ShaderDataType::Double4:	return 8 * 4;

		case ShaderDataType::Mat2:		return 4 * 2 * 2;
		case ShaderDataType::Mat3:		return 4 * 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4 * 4;
		}
	}

	/**
	* @brief      Retrieves the number of elements in a shader datatype
	*
	* @param type The type to calculate the element count of
	* @retuens    The number of elements in the type
	*/
	static uint32_t ShaderDataTypeCount(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:
		case ShaderDataType::Int:
		case ShaderDataType::Uint:
		case ShaderDataType::Float:
		case ShaderDataType::Double:
			return 1;

		case ShaderDataType::Bool2:
		case ShaderDataType::Int2:
		case ShaderDataType::Uint2:
		case ShaderDataType::Float2:
		case ShaderDataType::Double2:
			return 2;

		case ShaderDataType::Bool3:
		case ShaderDataType::Int3:
		case ShaderDataType::Uint3:
		case ShaderDataType::Float3:
		case ShaderDataType::Double3:
			return 3;

		case ShaderDataType::Bool4:
		case ShaderDataType::Int4:
		case ShaderDataType::Uint4:
		case ShaderDataType::Float4:
		case ShaderDataType::Double4:
			return 4;

		case ShaderDataType::Mat2:		return 2 * 2;
		case ShaderDataType::Mat3:		return 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4;
		}
	}

QK_PHOTON_END
