#pragma once

#include <type_traits>
#include <iostream>

#include "Math.h"

template <typename T>
concept number = std::is_arithmetic<T>::value;

template <number T>
class Vector2 {
public:
	Vector2()
		: x{}, y{} { }

	Vector2(T x, T y)
		: x{ x }, y{ y } { }

	void print() {
		std::cout << '(' << x << ", " << y << ")\n";
	}

	T x;
	T y;
};
