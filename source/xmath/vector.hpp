#pragma once

#include "defines.hpp"

namespace xmath
{
	template<size_t _Dimentions, typename T = number>
	class vector
	{
	private:
		T _value[_Dimentions];
	public:
		vector()
		{
			if(_Dimentions < 1)
				throw std::out_of_range("_Dimentions must be greater than 0");
			
			for(int i = 0;i < _Dimentions;i++)
					_value[i] = static_cast<T>(0.0);
		}

		vector(T* data)
		{
			for(int i = 0;i < _Dimentions;i++)
				_value[i] = data[i];
		}

		// vector(T data[_Dimentions]) : vector(data) { };

		template<size_t _Any>
		vector(matrix<_Dimentions,_Any,T>& m,int col = 0)
		{
			if(col < 0 || col >= _Any)
				throw std::out_of_range("Column index must be greater than or equal 0 and less than _Any");

			for(int i = 0;i < _Dimentions;i++)
				_value[i] = m.get_value(i, col);
		}

		T dot(vector<_Dimentions,T> vec) const
		{
			T result = ZERO(T);

			for(int i = 0;i < _Dimentions;i++)
				result += _value[i] * vec._value[i];

			return result;
		}

		vector<_Dimentions,T> cross(vector<_Dimentions,T> vec) const
		{
			if(_Dimentions != 3)
				throw std::out_of_range("Number of dimensions must be equal to 3 for cross product");

			T res[_Dimentions] = {
				_value[1] * vec._value[2] - _value[2] * vec._value[1],
				_value[2] * vec._value[0] - _value[0] * vec._value[2],
				_value[0] * vec._value[1] - _value[1] * vec._value[0],
			};

			return vector<_Dimentions,T>(res);
		}

		matrix<_Dimentions,1,T> to_matrix() const
		{
			return matrix<_Dimentions,1,T>(*this);
		}
		
		T get_element(int num) const { return _value[num]; }
		void set_element(int num,T value) { _value[num] = value; }
		
		T operator[] (int num) const { return _value[num]; }
		T& operator[] (int num) { return _value[num]; }

		T operator*(vector<_Dimentions,T>& vec) { return dot(vec); }
	};

#define VECTOR(n) using vector##n = vector<n>;
	VECTOR(1)
	VECTOR(2)
	VECTOR(3)
	VECTOR(4)
	VECTOR(5)
#undef VECTOR
}