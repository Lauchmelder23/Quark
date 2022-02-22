#pragma once

#include <glm/glm.hpp>

QK_PHOTON_BEGIN

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetPosition(const glm::vec3& position);
		const glm::vec3& GetPosition() const { return m_Position; }

		void SetRotation(float rotation);
		const float GetRotation() { return m_Rotation; }

		const glm::mat4& GetProjection() const { return m_Projection; }
		const glm::mat4& GetView() const { return m_View; }
		const glm::mat4& GetViewProjection() const { return m_ViewProjection; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_Projection;
		glm::mat4 m_View;
		glm::mat4 m_ViewProjection;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};

QK_PHOTON_END
