#pragma once

struct oxyVec2;
struct oxyVec3;
struct oxyVec4;
struct oxyQuat;
struct oxyMat4x4;

namespace oxygen
{
	namespace Math
	{
		static inline constexpr auto Pi = 3.14159265358979323846f;
		static inline constexpr auto TwoPi = 2.0f * Pi;
		static inline constexpr auto HalfPi = 0.5f * Pi;

		static inline constexpr auto RadToDeg = 180.0f / Pi;
		static inline constexpr auto DegToRad = Pi / 180.0f;
	}; // namespace Math
};	   // namespace oxygen

inline auto operator-(const oxyVec2& a) -> oxyVec2;
inline auto operator+(const oxyVec2& a, const oxyVec2& b) -> oxyVec2;
inline auto operator-(const oxyVec2& a, const oxyVec2& b) -> oxyVec2;
inline auto operator*(const oxyVec2& a, const oxyVec2& b) -> oxyVec2;
inline auto operator/(const oxyVec2& a, const oxyVec2& b) -> oxyVec2;
inline auto operator*(const oxyVec2& a, oxyF32 b) -> oxyVec2;
inline auto operator/(const oxyVec2& a, oxyF32 b) -> oxyVec2;

inline auto operator-(const oxyVec3& a) -> oxyVec3;
inline auto operator+(const oxyVec3& a, const oxyVec3& b) -> oxyVec3;
inline auto operator-(const oxyVec3& a, const oxyVec3& b) -> oxyVec3;
inline auto operator*(const oxyVec3& a, const oxyVec3& b) -> oxyVec3;
inline auto operator/(const oxyVec3& a, const oxyVec3& b) -> oxyVec3;
inline auto operator*(const oxyVec3& a, oxyF32 b) -> oxyVec3;
inline auto operator/(const oxyVec3& a, oxyF32 b) -> oxyVec3;

inline auto operator-(const oxyVec4& a) -> oxyVec4;
inline auto operator+(const oxyVec4& a, const oxyVec4& b) -> oxyVec4;
inline auto operator-(const oxyVec4& a, const oxyVec4& b) -> oxyVec4;
inline auto operator*(const oxyVec4& a, const oxyVec4& b) -> oxyVec4;
inline auto operator/(const oxyVec4& a, const oxyVec4& b) -> oxyVec4;
inline auto operator*(const oxyVec4& a, oxyF32 b) -> oxyVec4;
inline auto operator/(const oxyVec4& a, oxyF32 b) -> oxyVec4;

inline auto operator*(const oxyMat4x4& a, const oxyMat4x4& b) -> oxyMat4x4;
inline auto operator*(const oxyMat4x4& a, const oxyVec4& b) -> oxyVec4;

inline auto operator*(const oxyQuat& a, const oxyQuat& b) -> oxyQuat;
inline auto operator*(const oxyQuat& a, const oxyVec3& b) -> oxyVec3;
inline auto operator*(const oxyQuat& a, const oxyMat4x4& b) -> oxyMat4x4;

struct oxyVec2
{
	oxyF32 x, y;

	auto MagnitudeSquared() const -> oxyF32
	{
		return x * x + y * y;
	}
	auto Magnitude() const -> oxyF32
	{
		return std::sqrtf(x * x + y * y);
	}

	auto Normalized() const -> oxyVec2
	{
		oxyF32 mag = Magnitude();
		return {x / mag, y / mag};
	}
	auto Normalize() -> oxyVec2&
	{
		oxyF32 mag = Magnitude();
		x /= mag;
		y /= mag;
		return *this;
	}

	auto DotProduct(const oxyVec2& other) const -> oxyF32
	{
		return x * other.x + y * other.y;
	}

	auto CrossProduct(const oxyVec2& other) const -> oxyF32
	{
		return x * other.y - y * other.x;
	}

	auto Conjugate() const -> oxyVec2
	{
		return {-x, -y};
	}

	auto Inversed() const -> oxyVec2
	{
		return Conjugate() / (x * x + y * y);
	}
	auto Inverse() -> oxyVec2&
	{
		*this = Inversed();
		return *this;
	}

	auto operator+=(const oxyVec2& other) -> oxyVec2&
	{
		*this = *this + other;
		return *this;
	}
	auto operator-=(const oxyVec2& other) -> oxyVec2&
	{
		*this = *this - other;
		return *this;
	}
	auto operator*=(const oxyVec2& other) -> oxyVec2&
	{
		*this = *this * other;
		return *this;
	}
	auto operator/=(const oxyVec2& other) -> oxyVec2&
	{
		*this = *this / other;
		return *this;
	}
	auto operator*=(oxyF32 other) -> oxyVec2&
	{
		*this = *this * other;
		return *this;
	}
	auto operator/=(oxyF32 other) -> oxyVec2&
	{
		*this = *this / other;
		return *this;
	}
};

struct oxyVec3
{
	oxyF32 x, y, z;

	auto MagnitudeSquared() const -> oxyF32
	{
		return x * x + y * y + z * z;
	}
	auto Magnitude() const -> oxyF32
	{
		return std::sqrtf(x * x + y * y + z * z);
	}

	auto Normalized() const -> oxyVec3
	{
		oxyF32 mag = Magnitude();
		return {x / mag, y / mag, z / mag};
	}
	auto Normalize() -> oxyVec3&
	{
		oxyF32 mag = Magnitude();
		x /= mag;
		y /= mag;
		z /= mag;
		return *this;
	}

	auto DotProduct(const oxyVec3& other) const -> oxyF32
	{
		return x * other.x + y * other.y + z * other.z;
	}

	auto CrossProduct(const oxyVec3& other) const -> oxyVec3
	{
		return {y * other.z - z * other.y, z * other.x - x * other.z,
				x * other.y - y * other.x};
	}

	auto Conjugate() const -> oxyVec3
	{
		return {-x, -y, z};
	}

	auto Inversed() const -> oxyVec3
	{
		return Conjugate() / (x * x + y * y + z * z);
	}
	auto Inverse() -> oxyVec3&
	{
		*this = Inversed();
		return *this;
	}

	auto operator+=(const oxyVec3& other) -> oxyVec3&
	{
		*this = *this + other;
		return *this;
	}
	auto operator-=(const oxyVec3& other) -> oxyVec3&
	{
		*this = *this - other;
		return *this;
	}
	auto operator*=(const oxyVec3& other) -> oxyVec3&
	{
		*this = *this * other;
		return *this;
	}
	auto operator/=(const oxyVec3& other) -> oxyVec3&
	{
		*this = *this / other;
		return *this;
	}
	auto operator*=(oxyF32 other) -> oxyVec3&
	{
		*this = *this * other;
		return *this;
	}
	auto operator/=(oxyF32 other) -> oxyVec3&
	{
		*this = *this / other;
		return *this;
	}
};

struct oxyVec4
{
	oxyF32 x, y, z, w;

	auto MagnitudeSquared() const -> oxyF32
	{
		return x * x + y * y + z * z + w * w;
	}
	auto Magnitude() const -> oxyF32
	{
		return std::sqrtf(x * x + y * y + z * z + w * w);
	}

	auto Normalized() const -> oxyVec4
	{
		oxyF32 mag = Magnitude();
		return {x / mag, y / mag, z / mag, w / mag};
	}
	auto Normalize() -> oxyVec4&
	{
		oxyF32 mag = Magnitude();
		x /= mag;
		y /= mag;
		z /= mag;
		w /= mag;
		return *this;
	}

	auto DotProduct(const oxyVec4& other) const -> oxyF32
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	auto Conjugate() const -> oxyVec4
	{
		return {-x, -y, -z, w};
	}

	auto Inversed() const -> oxyVec4
	{
		return Conjugate() / (x * x + y * y + z * z + w * w);
	}
	auto Inverse() -> oxyVec4&
	{
		*this = Inversed();
		return *this;
	}

	auto operator+=(const oxyVec4& other) -> oxyVec4&
	{
		*this = *this + other;
		return *this;
	}
	auto operator-=(const oxyVec4& other) -> oxyVec4&
	{
		*this = *this - other;
		return *this;
	}
	auto operator*=(const oxyVec4& other) -> oxyVec4&
	{
		*this = *this * other;
		return *this;
	}
	auto operator/=(const oxyVec4& other) -> oxyVec4&
	{
		*this = *this / other;
		return *this;
	}
	auto operator*=(oxyF32 other) -> oxyVec4&
	{
		*this = *this * other;
		return *this;
	}
	auto operator/=(oxyF32 other) -> oxyVec4&
	{
		*this = *this / other;
		return *this;
	}
};

struct oxyMat4x4
{
	oxyF32 m[4][4];

	auto Determinant() const -> oxyF32
	{
		return m[0][0] * m[1][1] * m[2][2] * m[3][3] +
			   m[0][0] * m[1][2] * m[2][3] * m[3][1] +
			   m[0][0] * m[1][3] * m[2][1] * m[3][2] +
			   m[0][1] * m[1][0] * m[2][3] * m[3][2] +
			   m[0][1] * m[1][2] * m[2][0] * m[3][3] +
			   m[0][1] * m[1][3] * m[2][2] * m[3][0] +
			   m[0][2] * m[1][0] * m[2][1] * m[3][3] +
			   m[0][2] * m[1][1] * m[2][3] * m[3][0] +
			   m[0][2] * m[1][3] * m[2][0] * m[3][1] +
			   m[0][3] * m[1][0] * m[2][2] * m[3][1] +
			   m[0][3] * m[1][1] * m[2][0] * m[3][2] +
			   m[0][3] * m[1][2] * m[2][1] * m[3][0] -
			   m[0][0] * m[1][1] * m[2][3] * m[3][2] -
			   m[0][0] * m[1][2] * m[2][1] * m[3][3] -
			   m[0][0] * m[1][3] * m[2][2] * m[3][1] -
			   m[0][1] * m[1][0] * m[2][2] * m[3][3] -
			   m[0][1] * m[1][2] * m[2][3] * m[3][0] -
			   m[0][1] * m[1][3] * m[2][0] * m[3][2] -
			   m[0][2] * m[1][0] * m[2][3] * m[3][1] -
			   m[0][2] * m[1][1] * m[2][0] * m[3][3] -
			   m[0][2] * m[1][3] * m[2][1] * m[3][0] -
			   m[0][3] * m[1][0] * m[2][1] * m[3][2] -
			   m[0][3] * m[1][1] * m[2][2] * m[3][0] -
			   m[0][3] * m[1][2] * m[2][0] * m[3][1];
	}

	auto Transposed() const -> oxyMat4x4
	{
		oxyMat4x4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.m[i][j] = m[j][i];
			}
		}
		return result;
	}
	auto Transpose() -> oxyMat4x4&
	{
		*this = Transposed();
		return *this;
	}

	auto operator[](int i) -> oxyF32*
	{
		return m[i];
	}
	auto operator[](int i) const -> const oxyF32*
	{
		return m[i];
	}

	auto operator*=(const oxyMat4x4& other) -> oxyMat4x4&
	{
		*this = *this * other;
		return *this;
	}

	static inline auto Identity() -> oxyMat4x4
	{
		oxyMat4x4 result{};
		result.m[0][0] = 1;
		result.m[1][1] = 1;
		result.m[2][2] = 1;
		result.m[3][3] = 1;
		return result;
	}
};

struct oxyQuat
{
	oxyF32 x, y, z, w;

	auto MagnitudeSquared() const -> oxyF32
	{
		return x * x + y * y + z * z + w * w;
	}
	auto Magnitude() const -> oxyF32
	{
		return std::sqrtf(x * x + y * y + z * z + w * w);
	}

	auto Normalized() const -> oxyQuat
	{
		oxyF32 mag = Magnitude();
		return {x / mag, y / mag, z / mag, w / mag};
	}
	auto Normalize() -> oxyQuat&
	{
		oxyF32 mag = Magnitude();
		x /= mag;
		y /= mag;
		z /= mag;
		w /= mag;
		return *this;
	}

	auto DotProduct(const oxyQuat& other) const -> oxyF32
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	auto Conjugate() const -> oxyQuat
	{
		return {-x, -y, -z, w};
	}

	auto Inversed() const -> oxyQuat
	{
		const auto conj = Conjugate();
		const auto magsq = MagnitudeSquared();
		return {conj.x / magsq, conj.y / magsq, conj.z / magsq, conj.w / magsq};
	}
	auto Inverse() -> oxyQuat&
	{
		*this = Inversed();
		return *this;
	}

	auto operator*=(const oxyQuat& other) -> oxyQuat&
	{
		*this = *this * other;
		return *this;
	}
};

inline auto operator-(const oxyVec2& a) -> oxyVec2
{
	return {-a.x, -a.y};
}
inline auto operator+(const oxyVec2& a, const oxyVec2& b) -> oxyVec2
{
	return {a.x + b.x, a.y + b.y};
}
inline auto operator-(const oxyVec2& a, const oxyVec2& b) -> oxyVec2
{
	return {a.x - b.x, a.y - b.y};
}
inline auto operator*(const oxyVec2& a, const oxyVec2& b) -> oxyVec2
{
	return {a.x * b.x, a.y * b.y};
}
inline auto operator/(const oxyVec2& a, const oxyVec2& b) -> oxyVec2
{
	return {a.x / b.x, a.y / b.y};
}
inline auto operator*(const oxyVec2& a, oxyF32 b) -> oxyVec2
{
	return {a.x * b, a.y * b};
}
inline auto operator/(const oxyVec2& a, oxyF32 b) -> oxyVec2
{
	return {a.x / b, a.y / b};
}

inline auto operator-(const oxyVec3& a) -> oxyVec3
{
	return {-a.x, -a.y, -a.z};
}
inline auto operator+(const oxyVec3& a, const oxyVec3& b) -> oxyVec3
{
	return {a.x + b.x, a.y + b.y, a.z + b.z};
}
inline auto operator-(const oxyVec3& a, const oxyVec3& b) -> oxyVec3
{
	return {a.x - b.x, a.y - b.y, a.z - b.z};
}
inline auto operator*(const oxyVec3& a, const oxyVec3& b) -> oxyVec3
{
	return {a.x * b.x, a.y * b.y, a.z * b.z};
}
inline auto operator/(const oxyVec3& a, const oxyVec3& b) -> oxyVec3
{
	return {a.x / b.x, a.y / b.y, a.z / b.z};
}
inline auto operator*(const oxyVec3& a, oxyF32 b) -> oxyVec3
{
	return {a.x * b, a.y * b, a.z * b};
}
inline auto operator/(const oxyVec3& a, oxyF32 b) -> oxyVec3
{
	return {a.x / b, a.y / b, a.z / b};
}

inline auto operator-(const oxyVec4& a) -> oxyVec4
{
	return {-a.x, -a.y, -a.z, -a.w};
}
inline auto operator+(const oxyVec4& a, const oxyVec4& b) -> oxyVec4
{
	return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}
inline auto operator-(const oxyVec4& a, const oxyVec4& b) -> oxyVec4
{
	return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}
inline auto operator*(const oxyVec4& a, const oxyVec4& b) -> oxyVec4
{
	return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
}
inline auto operator/(const oxyVec4& a, const oxyVec4& b) -> oxyVec4
{
	return {a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
}
inline auto operator*(const oxyVec4& a, oxyF32 b) -> oxyVec4
{
	return {a.x * b, a.y * b, a.z * b, a.w * b};
}
inline auto operator/(const oxyVec4& a, oxyF32 b) -> oxyVec4
{
	return {a.x / b, a.y / b, a.z / b, a.w / b};
}

inline auto operator*(const oxyMat4x4& a, const oxyMat4x4& b) -> oxyMat4x4
{
	oxyMat4x4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] +
							 a.m[i][2] * b.m[2][j] + a.m[i][3] * b.m[3][j];
		}
	}
	return result;
}
inline auto operator*(const oxyMat4x4& a, const oxyVec4& b) -> oxyVec4
{
	oxyVec4 result;
	for (int i = 0; i < 4; i++)
	{
		result.x += a.m[i][0] * b.x;
		result.y += a.m[i][1] * b.y;
		result.z += a.m[i][2] * b.z;
		result.w += a.m[i][3] * b.w;
	}
	return result;
}

inline auto operator*(const oxyQuat& a, const oxyQuat& b) -> oxyQuat
{
	return {a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
			a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
			a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
			a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z};
}
inline auto operator*(const oxyQuat& a, const oxyVec3& b) -> oxyVec3
{
	oxyQuat v = {b.x, b.y, b.z, 0};
	oxyQuat result = a * v * a.Conjugate();
	return {result.x, result.y, result.z};
}
inline auto operator*(const oxyQuat& a, const oxyMat4x4& b) -> oxyMat4x4
{
	oxyMat4x4 result;
	result.m[0][0] = 1 - 2 * a.y * a.y - 2 * a.z * a.z;
	result.m[0][1] = 2 * a.x * a.y - 2 * a.z * a.w;
	result.m[0][2] = 2 * a.x * a.z + 2 * a.y * a.w;
	result.m[0][3] = 0;
	result.m[1][0] = 2 * a.x * a.y + 2 * a.z * a.w;
	result.m[1][1] = 1 - 2 * a.x * a.x - 2 * a.z * a.z;
	result.m[1][2] = 2 * a.y * a.z - 2 * a.x * a.w;
	result.m[1][3] = 0;
	result.m[2][0] = 2 * a.x * a.z - 2 * a.y * a.w;
	result.m[2][1] = 2 * a.y * a.z + 2 * a.x * a.w;
	result.m[2][2] = 1 - 2 * a.x * a.x - 2 * a.y * a.y;
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;
	return result * b;
}

namespace oxygen
{
	namespace Math
	{
		inline auto Translate(const oxyMat4x4& m, const oxyVec3& v) -> oxyMat4x4
		{
			oxyMat4x4 result = m;
			result.m[3][0] += v.x;
			result.m[3][1] += v.y;
			result.m[3][2] += v.z;
			return result;
		}
		inline auto Rotate(const oxyMat4x4& m, const oxyQuat& q) -> oxyMat4x4
		{
			oxyMat4x4 result;
			result.m[0][0] = 1 - 2 * q.y * q.y - 2 * q.z * q.z;
			result.m[0][1] = 2 * q.x * q.y - 2 * q.z * q.w;
			result.m[0][2] = 2 * q.x * q.z + 2 * q.y * q.w;
			result.m[0][3] = 0;
			result.m[1][0] = 2 * q.x * q.y + 2 * q.z * q.w;
			result.m[1][1] = 1 - 2 * q.x * q.x - 2 * q.z * q.z;
			result.m[1][2] = 2 * q.y * q.z - 2 * q.x * q.w;
			result.m[1][3] = 0;
			result.m[2][0] = 2 * q.x * q.z - 2 * q.y * q.w;
			result.m[2][1] = 2 * q.y * q.z + 2 * q.x * q.w;
			result.m[2][2] = 1 - 2 * q.x * q.x - 2 * q.y * q.y;
			result.m[2][3] = 0;
			result.m[3][0] = 0;
			result.m[3][1] = 0;
			result.m[3][2] = 0;
			result.m[3][3] = 1;
			return result * m;
		}
		inline auto Scale(const oxyMat4x4& m, const oxyVec3& v) -> oxyMat4x4
		{
			oxyMat4x4 result = m;
			result.m[0][0] *= v.x;
			result.m[1][1] *= v.y;
			result.m[2][2] *= v.z;
			return result;
		}
		inline auto LookAt(const oxyVec3& eye, const oxyVec3& center,
						   const oxyVec3& up) -> oxyMat4x4
		{
			const auto f = (center - eye).Normalized();
			const auto s = f.CrossProduct(up).Normalized();
			const auto u = s.CrossProduct(f);
			oxyMat4x4 result{};
			result[0][0] = s.x;
			result[1][0] = s.y;
			result[2][0] = s.z;
			result[0][1] = u.x;
			result[1][1] = u.y;
			result[2][1] = u.z;
			result[0][2] = -f.x;
			result[1][2] = -f.y;
			result[2][2] = -f.z;
			result[3][0] = -s.DotProduct(eye);
			result[3][1] = -u.DotProduct(eye);
			result[3][2] = f.DotProduct(eye);
			result[3][3] = 1;
			return result;
		}
		inline auto Perspective(oxyF32 fovy, oxyF32 aspect, oxyF32 near,
								oxyF32 far) -> oxyMat4x4
		{
			const auto tanHalfFovy = std::tanf(fovy / 2.f);
			oxyMat4x4 result{};
			result[0][0] = 1.f / (aspect * std::tanf(fovy / 2.f));
			result[1][1] = 1.f / std::tanf(fovy / 2.f);
			result[2][2] = far / (far - near);
			result[2][3] = 1.f;
			result[3][2] = -(far * near) / (far - near);
			return result;
		}
		inline auto RotationMatrixToEuler(const oxyMat4x4& m) -> oxyVec3
		{
			oxyVec3 result;
			result.y = std::asin(-m[2][0]);
			if (std::cos(result.y) != 0)
			{
				result.x = std::atan2(m[2][1], m[2][2]);
				result.z = std::atan2(m[1][0], m[0][0]);
			}
			else
			{
				result.x = 0;
				result.z = std::atan2(-m[0][1], m[1][1]);
			}
			return result;
		}
		inline auto AngleAxisToQuat(const oxyF32 angle, const oxyVec3& axis)
			-> oxyQuat
		{
			const auto halfAngle = angle / 2;
			const auto s = std::sin(halfAngle);
			return {axis.x * s, axis.y * s, axis.z * s, std::cos(halfAngle)};
		}
		inline auto QuatToEulerAngles(const oxyQuat& q) -> oxyVec3
		{
			oxyVec3 result;
			result.x = std::atan2(2 * (q.w * q.x + q.y * q.z),
								  1 - 2 * (q.x * q.x + q.y * q.y));
			result.y = std::asin(2 * (q.w * q.y - q.z * q.x));
			result.z = std::atan2(2 * (q.w * q.z + q.x * q.y),
								  1 - 2 * (q.y * q.y + q.z * q.z));
			return result;
		}
		inline auto EulerAnglesToQuat(const oxyVec3& v) -> oxyQuat
		{
			const auto pitch = AngleAxisToQuat(v.x, {1, 0, 0});
			const auto yaw = AngleAxisToQuat(v.y, {0, 1, 0});
			const auto roll = AngleAxisToQuat(v.z, {0, 0, 1});
			return pitch * yaw * roll;
		}
	}; // namespace Math
};	   // namespace oxygen