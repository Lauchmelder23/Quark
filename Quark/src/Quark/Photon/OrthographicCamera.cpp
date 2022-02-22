#include "qkpch.hpp"
#include "OrthographicCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

QK_PHOTON_BEGIN

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) :
		m_Projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_View(1.0f), m_Position(0.0f)
	{
		m_ViewProjection = m_Projection * m_View;
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);
		transform = glm::rotate(transform, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		m_View = glm::inverse(transform);
		m_ViewProjection = m_Projection * m_View;
	}

QK_PHOTON_END
