/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** vec
*/

#ifndef CPP_INDIE_STUDIO_VEC3D_HPP
#define CPP_INDIE_STUDIO_VEC3D_HPP

template<typename T>
class vec3d {
public:
	vec3d() = default;
	vec3d(T value1, T value2 , T value3) : x(value1),
					       y(value2),
					       z(value3)
	{}
	~vec3d() = default;
	vec3d operator+(vec3d &v) {
		return vec3d(x + v.x, y + v.y, z + v.z);
	}

	vec3d operator-(vec3d &v) {
		return vec3d(x - v.x, y - v.y, z - v.z);
	}

	vec3d& operator+=(vec3d& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec3d& operator-=(vec3d& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	T x;
	T y;
	T z;
};

	template<typename T>
	class vec2d {
	public:
		vec2d() = default;
		vec2d(T value1, T value2) : x(value1), y(value2)
		{}
		~vec2d() = default;
	bool operator==(const vec2d &other) const
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(const vec2d &other) const
		{
			return !(other == *this);
		}	vec2d operator+(const vec2d &v) {
			return vec2d(x + v.x, y + v.y);
		}

	vec2d operator-(const vec2d &v) {
		return vec2d(x - v.x, y - v.y);
	}

	vec2d &operator+=(const vec2d &v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	vec2d &operator-=(const vec2d &v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	T x;
	T y;
};

template<class T>
vec2d<T> roundPos(const vec2d<float> &pos) {
	return {static_cast<T>(std::lround(pos.x)),
		static_cast<T>(std::lround(pos.y))};
}

template<class T>
vec2d<T> roundPos(float x, float y) {
	return {static_cast<T>(std::lround(x)),
		static_cast<T>(std::lround(y))};
}

#endif //CPP_INDIE_STUDIO_VEC3D_HPP
