#pragma once

#include <glm/glm.hpp>

namespace Mango {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);
		
		const glm::vec3& GetPosition() { return m_Position; }
		inline void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); };

		float GetRotation() { return m_Rotation; }
		inline void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4 GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4 GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix = glm::mat4(1);
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = glm::vec3(0.0f);
		float m_Rotation = 0.0f;
	};
}
