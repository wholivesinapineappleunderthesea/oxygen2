#pragma once

namespace oxygen
{
	struct DebugCamera : SingletonBase<DebugCamera>
	{
		oxyBool m_isOverriding{true}; // for now

		oxyVec3 m_position{0.0f, 0.0f, 0.0f};
		oxyQuat m_rotation{};
		oxyF32 m_vfov{60.f};
		oxyF32 m_nearPlane{0.01f};
		oxyF32 m_farPlane{1000.0f};

		oxyMat4x4 m_viewMatrix{};
		oxyMat4x4 m_projectionMatrix{};
		oxyMat4x4 m_viewProjectionMatrix{};

		auto ComputeMatrices() -> void;
	};
} // namespace oxygen