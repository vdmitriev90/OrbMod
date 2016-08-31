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
		//n - number of rows
		//m - number of columns
		size_t n, m, size;
		double* M;
		double m1;
		void initDim(const int & n, const int & m);
		//void init();

	public:
		Matrix();

		//constructors
		Matrix(const int & N, const int & M);
		Matrix(const alglib::real_2d_array &rArr);
		Matrix(const double *Arr, int N, int M);
		Matrix(const vector<double> &Vec, int N, int M, int offset);
		Matrix(const vector<double> &Vec);
		Matrix(triple Vec);

		//copy constructor
		Matrix(const Matrix &);
		~Matrix();

#pragma region CopyTo

		void ToOneDimArr(double *&vec) const;
		vector<vector<double>> ToTwoDimVector() const;
		void copyToVec(int offset, vector<double> &V) const;
#pragma endregion 
		void setFromVec(int offset, const vector<double> &V);

		void Clear();
		void Zero();
		void Identy();
		Matrix PrimeDiag()const;
		double Trace() const;
		Matrix Transpose();
		Matrix Inverse();
		double SumSq() const;
		static bool LeastSQRSolve(Matrix &A, Matrix &b, Matrix &X, Matrix &Q);
		static bool QRdecomp(Matrix &A, Matrix &Q, Matrix &R);
		Matrix subMatrix(int n0, int nSize, int m0, int mSize) const;
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

		friend triple operator*(const Matrix &left, const  triple &right);
		friend Matrix operator+(const Matrix &left, const  Matrix &right);
		friend Matrix operator-(const Matrix & left, const  Matrix & right);
		friend Matrix operator*(const double & left, const  Matrix & right);
		friend Matrix operator/(const Matrix & left, const double & right);
		friend Matrix operator*(const Matrix & left, const double & right);
		friend Matrix operator*(const Matrix & a, const Matrix & b);

		//assignment operator
		Matrix & operator = (const Matrix & other);

		//set-get indexer
		double &operator ()(int i, int j);
		//get-only indexer
		const double & Matrix:: operator ()(int i, int j) const;
		
		//indexers as method
		double &at(int i, int j);
		const double &at(int i, int j) const;

		void operator+=(const Matrix & right);
		void operator-=(const Matrix & right);
		void operator*=(const double & right);
		void operator/=(const double & right);

		//	void MatrixDecompose(vector<vector<double>> matrix, vector<int> b, int toggle);
		//	MatrixInverse(Matrix &matrix, Matrix &result);

	};
}
