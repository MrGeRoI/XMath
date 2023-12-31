#pragma once

#include "vector.hpp"

namespace xmath
{
	class non_square_matrix : std::exception
	{
	public:
		virtual const char* what() const { return "Matrix is not squared"; };
	};

	class abstract_matrix
	{
	public:
		virtual size_t rows() const = 0;
		virtual size_t columns() const = 0;
	};

	template<typename _Scalar = number>
	class dynamic_matrix : abstract_matrix
	{
	private:
		_Scalar** _value;
		size_t _rows,_columns;
	
	public:
		dynamic_matrix(size_t rows,size_t columns)
		{
			_rows = rows;
			_columns = columns;

			_value = new _Scalar[columns][];
			
			for(int i = 0;i < rows;i++)
			{
				_value[i] = new _Scalar[columns];

				for(int j = 0;j < columns;j++)
					_value[i][j] = (i == j) ? ONE(_Scalar) : ZERO(_Scalar);
			}
		}

		virtual size_t rows() const { return _rows; };
		virtual size_t columns() const { return _columns; };
	};

	template<size_t _Rows, size_t _Columns, typename _Scalar = number>
	class matrix : abstract_matrix
	{
	private:
		_Scalar _value[_Rows][_Columns];
	public:
		matrix()
		{
			if(_Rows < 1 || _Columns < 1)
				throw std::out_of_range("_Rows or _Columns must be greater than 0");
			
			for(int i = 0;i < _Rows;i++)
				for(int j = 0;j < _Columns;j++)
					_value[i][j] = ZERO(_Scalar);
		}

		matrix(vector<_Rows>& vec)
		{
			if(_Columns != 1)
				throw std::out_of_range("_Columns must be 1 when constructing from vector");

			for(int i = 0;i < _Rows;i++)
				_value[i][0] = vec.get_element(i);
		}

		matrix(_Scalar* data)
		{
			
		}

		virtual size_t rows() const { return _Rows; }
		virtual size_t columns() const { return _Columns; }

		vector<_Columns,_Scalar> row(int row) const
		{
			vector<_Columns> result;

			for(int i = 0;i < _Columns;i++)
				result.set_element(i, _value[row,i]);

			return result;
		}

		vector<_Rows,_Scalar> column(int col) const
		{
			vector<_Rows> result;

			for(int i = 0;i < _Rows;i++)
				result.set_element(i, _value[i,col]);

			return result;
		}

		_Scalar get_element(int row,int col) const { return _value[row,col]; }
		void set_element(int row,int col,_Scalar value) { _value[row,col] = value; }

		_Scalar determinant() const
		{
			if(_Rows != _Columns)
				throw non_square_matrix();
			
			return ZERO(_Scalar);
		}

		void transponise()
		{
			
		}

		matrix<_Columns, _Rows> transposed() const
		{
			matrix<_Columns, _Rows> result;

			return *this;
		}

		matrix<_Rows,_Columns> operator+(matrix<_Rows,_Columns> m) const
		{
			matrix<_Rows,_Columns> result;

			for(int i = 0;i < _Rows;i++)
				for(int j = 0;j < _Columns;j++)
					result._value[i][j] = _value[i][j] + m._value[i][j];

			return result;
		}
		
		matrix<_Rows,_Columns> operator-(matrix<_Rows,_Columns> m) const
		{
			matrix<_Rows,_Columns> result;

			for(int i = 0;i < _Rows;i++)
				for(int j = 0;j < _Columns;j++)
					result[i][j] = _value[i][j] - m._value[i][j];

			return result;
		}

		matrix<_Rows,_Columns> operator-() const
		{
			matrix<_Rows,_Columns> result;

			for(int i = 0;i < _Rows;i++)
				for(int j = 0;j < _Columns;j++)
					result[i,j] = -_value[i,j];

			return result;
		}

		template<size_t _Res>
		matrix<_Rows,_Res> operator*(matrix<_Columns,_Res> m) const
		{
			matrix<_Rows,_Res> result;
			
			return result;
		}

		vector<_Rows> operator*(vector<_Columns> vec) const
		{
			vector<_Rows> result;
			
			return result;
		}

		void operator ++ ()
		{
			if(_Rows != _Columns)
				throw non_square_matrix();

			for(int i = 0;i < _Rows;i++)
				_value[i,i]++;
		}

		_Scalar operator[] (int col) const { return column(col); }
		_Scalar operator*() const
		{
			if(_Rows == _Columns)
				return determinant();
			
			return sqrt(((*this) * transposed()).determinant());

			//throw non_square_matrix();
		}
	};

#define MATRIX(a,b) using matrix##a##x##b = matrix<a,b>;
	MATRIX(1,1)

	MATRIX(1,2)
	MATRIX(2,1)
	MATRIX(2,2)

	MATRIX(3,1)
	MATRIX(3,2)
	MATRIX(3,3)
	MATRIX(2,3)
	MATRIX(1,3)

	MATRIX(4,1)
	MATRIX(4,2)
	MATRIX(4,3)
	MATRIX(4,4)
	MATRIX(3,4)
	MATRIX(2,4)
	MATRIX(1,4)
#undef MATRIX
}