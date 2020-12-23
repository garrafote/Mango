#pragma once

#include <glm/glm.hpp>

namespace Mango {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{

		}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};

	template<typename T, glm::qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR glm::vec<4, T, Q> operator*(glm::vec<4, T, Q> const& v, Timestep scalar)
	{
		return glm::vec<4, T, Q>(
			v.x * scalar,
			v.y * scalar,
			v.z * scalar,
			v.w * scalar);
	}
	
	template<typename T, glm::qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR glm::vec<3, T, Q> operator*(glm::vec<3, T, Q> const& v, Timestep scalar)
	{
		return glm::vec<3, T, Q>(
			v.x * scalar,
			v.y * scalar,
			v.z * scalar);
	}
	
	template<typename T, glm::qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR glm::vec<2, T, Q> operator*(glm::vec<2, T, Q> const& v, Timestep scalar)
	{
		return glm::vec<2, T, Q>(
			v.x * scalar,
			v.y * scalar);
	}
}
