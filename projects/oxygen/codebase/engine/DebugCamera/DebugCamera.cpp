#include "OxygenPCH.h"
#include "DebugCamera.h"
namespace oxygen
{
	auto DebugCamera::ComputeMatrices() -> void
	{
		const auto forward = m_rotation * oxyVec3{0.0f, 0.0f, 1.0f};
		const auto right = m_rotation * oxyVec3{1.0f, 0.0f, 0.0f};
		const auto up = m_rotation * oxyVec3{0.0f, 1.0f, 0.0f};

		m_viewMatrix = Math::LookAt(m_position, m_position + oxyVec3{forward},
									  oxyVec3{up});
		m_projectionMatrix = Math::Perspective(m_vfov, 16.0f / 9.0f,
													m_nearPlane, m_farPlane);
		m_viewProjectionMatrix = m_viewMatrix * m_projectionMatrix;
	}

}; // namespace oxygen