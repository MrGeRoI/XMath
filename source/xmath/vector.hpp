#pragma once

#include "defines.hpp"

namespace xmath
{
	template<size_t _Dimentions, typename _Scalar = number>
	class vector
	{
	private:
		_Scalar _value[_Dimentions];
	public:
		vector()
		{
			if(_Dimentions < 1)
				throw std::out_of_range("_Dimentions must be greater than 0");
			
			for(int i = 0;i < _Dimentions;i++)
					_value[i] = static_cast<_Scalar>(0.0);
		}

		vector(_Scalar* data)
		{
			for(int i = 0;i < _Dimentions;i++)
				_value[i] = data[i];
		}

		vector(const vector<_Dimentions,_Scalar>& vec)
		{
			for(int i = 0;i < _Dimentions;i++)
				_value[i] = vec._value[i];
		}

		// vector(_Scalar data[_Dimentions]) : vector(data) { };

		template<size_t _Any>
		vector(const matrix<_Dimentions,_Any,_Scalar>& m,int col = 0)
		{
			if(col < 0 || col >= _Any)
				throw std::out_of_range("Column index must be greater than or equal 0 and less than _Any");

			for(int i = 0;i < _Dimentions;i++)
				_value[i] = m.get_value(i, col);
		}

		_Scalar dot(const vector<_Dimentions,_Scalar>& vec) const
		{
			_Scalar result = ZERO(_Scalar);

			for(int i = 0;i < _Dimentions;i++)
				result += _value[i] * vec._value[i];

			return result;
		}

		vector<_Dimentions,_Scalar> cross(const vector<_Dimentions,_Scalar>& vec) const
		{
			
		}

		matrix<_Dimentions,1,_Scalar> to_matrix() const
		{
			return matrix<_Dimentions,1,_Scalar>(*this);
		}
		
		const _Scalar& operator[] (int num) const { return _value[num]; }
		_Scalar& operator[] (int num) { return _value[num]; }

		_Scalar operator*(const vector<_Dimentions,_Scalar>& vec) const { return dot(vec); }

		vector<_Dimentions,_Scalar> operator+(const vector<_Dimentions,_Scalar>& vec) const
		{
			vector<_Dimentions,_Scalar> result;

			for(int i = 0; i < _Dimentions.size(); i++)
				result._values[i] = _values[i] + vec._values[i];

			return result;
		}

		
		vector<_Dimentions,_Scalar> operator-(const vector<_Dimentions,_Scalar>& vec) const
		{
			vector<_Dimentions,_Scalar> result;

			for(int i = 0; i < _Dimentions.size(); i++)
				result._values[i] = _values[i] - vec._values[i];

			return result;
		}

		vector<_Dimentions,_Scalar> operator-() const
		{
			vector<_Dimentions,_Scalar> result;

			for(int i = 0; i < _Dimentions.size(); i++)
				result._values[i] = -_values[i];

			return result;
		}

		vector<_Dimentions,_Scalar> operator*(_Scalar scalar) const
		{
			vector<_Dimentions,_Scalar> result;

			for(int i = 0; i < _Dimentions.size(); i++)
				result._values[i] = _values[i] * scalar;

			return result;
		}

		vector<_Dimentions,_Scalar> operator/(_Scalar scalar) const
		{
			vector<_Dimentions,_Scalar> result;

			for(int i = 0; i < _Dimentions.size(); i++)
				result._values[i] = _values[i] / scalar;

			return result;
		}

		vector<_Dimentions,_Scalar>& operator=(const vector<_Dimentions,_Scalar>& vec)
		{
			for(int i = 0;i < _Dimentions;i++)
				_value[i] = vec._value[i];

			return *this;
		}
	};
	
	template<size_t _Dimentions, typename _Scalar>
	vector<_Dimentions,_Scalar> cross(const vector<_Dimentions,_Scalar>& Args...)
	{
		if(__VA_ARGS__ != _Dimentions)
			throw std::out_of_range("__VA_ARGS__ should be equal to _Dimentions");
	}

#define VECTOR(n) using vector##n = vector<n>;
	VECTOR(1)
	VECTOR(2)
	VECTOR(3)
	VECTOR(4)
	VECTOR(5)
#undef VECTOR
}