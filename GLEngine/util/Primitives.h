#pragma once
#include <memory>

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