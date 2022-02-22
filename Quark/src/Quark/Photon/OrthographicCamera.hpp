#pragma once

#include <glm/glm.hpp>

QK_PHOTON_BEGIN

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		inline void SetPosition(const glm::vec3& position) { m_Position = position; }
		const glm::vec3& GetPosition() const { return m_Position; }

		inline void SetRotation(float rotation) { m_Rotation = rotation; }
		const float GetRotation() { return m_Rotation; }

	private:
		glm::mat4 m_Projection;
		glm::mat4 m_View;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};

QK_PHOTON_END
