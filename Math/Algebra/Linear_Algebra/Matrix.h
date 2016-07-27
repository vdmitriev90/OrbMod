#pragma once
#include"stdafx.h"
#include "AlgLib\src\linalg.h"
//#include "Math\Algebra\Linear_Algebra\triple.h"
//#include"Math\Algebra\Linear_Algebra\triple.h"

using namespace std;
namespace Algebra
{
	enum Axis { X = 0, Y, Z };
	class Matrix
	{
	private:
		//n - число строк
		//m - число столбцов
		size_t n, m, size;
		double* M;

		void initDim(const int & n, const int & m);
		//void init();

	public:
		Matrix();

		//конструкторы
		Matrix(const int & N, const int & M);
		Matrix(const alglib::real_2d_array &rArr);
		Matrix(const double *Arr, int N, int M);
		Matrix(const vector<double> &Vec, int N, int M, int offset);
		Matrix(const vector<double> &Vec);
		Matrix(triple Vec);

		//конструктор копирования
		Matrix(const Matrix &);
		~Matrix();

#pragma region CopyTo

		void ToOneDimArr(double *&vec) const;
		vector<vector<double>> ToTwoDimVector();
		void copyToVec(int offset, vector<double> &V);
#pragma endregion 
		void setFromVec(int offset, const vector<double> &V);

		void Clear();
		void Zero();
		void Identy();
		Matrix PrimeDiag();
		double Trace();
		Matrix Transpose();
		Matrix Inverse();
		static bool LeastSQRSolve(Matrix &A, Matrix &b, Matrix &X, Matrix &Q);
		static bool QRdecomp(Matrix &A, Matrix &Q, Matrix &R);
		Matrix subMatrix(int n0, int nSize, int m0, int mSize);
		void addRows(const Matrix &newRow);
		//
		size_t nCols() const
		{
			return this->m;
		}
		size_t nRows() const
		{
			return this->n;
		}
		size_t Size() const
		{
			return size;
		}
		//
		void Rotate(Axis axis, double angle);

		double MaxMod();
		std::string toString() const;
		std::string toString(char* sep) const;
		std::string toString(char* sep, char* format, int len) const;
		std::string toString(char* sep, char* format, int len, int isSplitByRows) const;

		friend triple operator*(Matrix &left, triple &right);
		friend Matrix operator+(Matrix &left, Matrix &right);
		friend Matrix operator-(Matrix & left, Matrix & right);
		friend Matrix operator*(const double & left, Matrix & right);
		friend Matrix operator/(Matrix & left, const double & right);
		friend Matrix operator*(Matrix & left, const double & right);
		friend Matrix operator*(Matrix & a, Matrix & b);

		//оператор присваивания
		Matrix & operator = (const Matrix & other);

		//взятие/присваивание элемента по индексу
		double  &operator ()(int i, int j);

		void operator+=(const  Matrix & right);
		void operator-=(const  Matrix & right);
		void operator*=(const double & right);
		void operator/=(const  double & right);

		//	void MatrixDecompose(vector<vector<double>> matrix, vector<int> b, int toggle);
		//	MatrixInverse(Matrix &matrix, Matrix &result);

	};
}
