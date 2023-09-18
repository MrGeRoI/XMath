#pragma once

#include "defines.hpp"

namespace xmath
{
	template<typename T = integer>
	class rational
	{
	private:
		T _numerator;
		T _denominator;

	public:
		rational()
		{
			_numerator = ZERO(T);
			_denominator = ONE(T);
		}

		rational(T numerator)
		{
			_numerator = numerator;
			_denominator = ONE(T);
		}

		rational(T numerator,T denominator)
		{
			_numerator = denominator >= 0 ? numerator : -numerator;
			_denominator = abs(denominator);
		}

		template<typename R = number>
		R value() const
		{
			return (R) _numerator / (R) _denominator;
		}

		template<typename T>
		friend math::rational<T> abs(math::rational<T> rat);
	};
}

template<typename T>
xmath::rational<T> abs(xmath::rational<T> rat)
{
	return xmath::rational<T>(abs(rat._numerator), rat._denominator);
}
