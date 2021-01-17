#include "MangoPCH.h"
#include"SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

Mango::SceneCamera::SceneCamera()
{
	RecalculateProjection();
}

void Mango::SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
{
	m_OrthographicSize = size;
	m_OrthographicNear = nearClip;
	m_OrthographicFar = farClip;

	RecalculateProjection();
}

void Mango::SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
{
	m_AspectRatio = (float)width / (float)height;

	RecalculateProjection();
}

void Mango::SceneCamera::RecalculateProjection()
{
	float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
	float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
	float orthoBottom = -m_OrthographicSize * 0.5f;
	float orthoTop = m_OrthographicSize * 0.5f;

	m_Projection = glm::ortho(orthoLeft, orthoRight,
		orthoTop, orthoBottom, m_OrthographicNear, m_OrthographicFar);
}
