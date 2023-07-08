#pragma once

#include <cmath>
#include <concepts>
#include <iostream>

#include "Math.h"


template <std::floating_point T>
class Vector2 {
public:
	Vector2()
		: x{}, y{} { }

	Vector2(T x, T y)
		: x{ x }, y{ y } { }

	Vector2<T> operator+(Vector2<T>& other) {
		Vector2<T> newVec{};
		newVec.x = this->x + other.x;
		newVec.y = this->y + other.y;
		return newVec;
	}

	Vector2<T> operator-(Vector2<T>& other) {
		Vector2<T> newVec{};
		newVec.x = this->x - other.x;
		newVec.y = this->y - other.y;
		return newVec;
	}

	void operator+=(Vector2<T>& other) {
		x = x + other.x;
		y = y + other.y;
	}

	void operator-=(Vector2<T>& other) {
		x = x - other.x;
		y = y - other.y;
	}

	Vector2<T> operator*(T scalar) {
		return Vector2<float>{ x*scalar, y*scalar };
	}

	void print() const {
		std::cout << '(' << x << ", " << y << ")\n";
	}

	T norm() const {
		return std::sqrt(x*x + y*y);
	}

	void normalize() {
		if (x != 0 || y != 0) {
			T norm = this->norm();
			x = x / norm;
			y = y / norm;
		}
	}

	T x;
	T y;
};
