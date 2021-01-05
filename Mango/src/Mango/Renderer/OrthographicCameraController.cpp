#include "MangoPCH.h"
#include "OrthographicCameraController.h"

#include "Mango/Core/Input.h"
#include "Mango/Core/KeyCodes.h"
#include <glm/gtx/quaternion.hpp>

namespace Mango {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio)
		, m_Rotation(rotation)
		, m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{

	}
	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		MGO_PROFILE_FUNCTION();

		glm::vec3 delta(0);
		float translationSpeed = m_CameraTranslationSpeed * m_ZoomLevel;
		if (Input::IsKeyPressed(MGO_KEY_A))
			delta.x -= translationSpeed;

		if (Input::IsKeyPressed(MGO_KEY_D))
			delta.x += translationSpeed;

		if (Input::IsKeyPressed(MGO_KEY_W))
			delta.y += translationSpeed;

		if (Input::IsKeyPressed(MGO_KEY_S))
			delta.y -= translationSpeed;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(MGO_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;

			if (Input::IsKeyPressed(MGO_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_CameraRotation = std::fmod(m_CameraRotation + 360.0f, 360.0f);

			glm::quat rotation = glm::angleAxis(glm::radians(m_CameraRotation), glm::vec3(0, 0, 1));
			m_CameraPosition += rotation * delta * ts;

			m_Camera.SetPosition(m_CameraPosition);
			m_Camera.SetRotation(m_CameraRotation);
		}
		else
		{
			m_CameraPosition += delta * ts;
			m_Camera.SetPosition(m_CameraPosition);
		}

	}
	void OrthographicCameraController::OnEvent(Event& e)
	{
		MGO_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(MGO_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(MGO_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		MGO_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.125f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.0125f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}
	
	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		MGO_PROFILE_FUNCTION();

		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}
}
