#pragma once

// C++ Libraries
#include <algorithm>
#include <vector>
#include <list>
#include <functional>
#include <map>
#include <stack>
#include <tuple>
#include <exception>

// C Libraries
#include <cmath>

// Useful Macros
#define ZERO(_TYPE) static_cast<_TYPE>(0)
#define ONE(_TYPE) static_cast<_TYPE>(1)

namespace xmath
{
	//change to anything
	using number = double;
	using integer = int;
	using default_typename = std::nullptr_t;

	template<typename T>
	class graph;

	template<size_t _Rows, size_t _Columns, typename _Scalar>
	class matrix;

	template<size_t _Dimentions, typename _Scalar>
	class vector;
}