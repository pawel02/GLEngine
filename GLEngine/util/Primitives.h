#pragma once
#include <memory>

struct Vec2
{
	float x;
	float y;
};

struct Vec3
{
	float x;
	float y;
	float z;
};

struct Vertex
{
	Vec3 Pos;
	Vec2 TexCoords;
	float TexID;
};

template<typename T>
struct Vector2
{
	T x;
	T y;

	explicit Vector2(T x, T y) noexcept
		:x{x}, y{y}
	{}

	explicit Vector2(Vector2&& other) noexcept
		:x{std::move(other.x)}, y{std::move(other.y)}
	{}
};